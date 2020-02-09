/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_malloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:38:09 by rreedy            #+#    #+#             */
/*   Updated: 2020/02/09 01:38:48 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "mem.h"
#include "struct_tsPageHeader.h"
#include "struct_tsAllocHeader.h"
#include "struct_lAllocHeader.h"
#include <sys/mman.h>
#include <stddef.h>
#include <unistd.h>

void		add_large_alloc(size_t used_size)
{
	struct s_lAllocHeader	*new_header;
	void					*new_alloc;
	size_t					size;

	size = (used_size / info->pagesize) + info->pagesize;
	new_alloc = mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (!new_alloc)
		return ;
	new_header = (struct s_lAllocHeader *)new_alloc;
	new_header->size = size;
	new_header->used = used_size;
	new_header->prev_alloc = 0;
	new_header->next_alloc = info->lallocs;
	info->lallocs->prev_alloc = new_header;
	info->lallocs = new_header;
}

static void			add_tiny_page(void *new_page)
{
	struct s_tsAllocHeader	*new_header;
	unsigned int			i;

	if (!info->tpages)
		info->tpages = (struct s_tsPageHeader *)new_page;
	else
		info->tpages_tail->next_page = (struct s_tsPageHeader *)new_page;
	new_header = (struct s_tsAllocHeader *)(new_page + TNY_PG_OFSET);
	if (!info->free_tallocs)
		info->free_tallocs = new_header;
	else
		info->free_tallocs_tail->next_free = new_header;
	new_header->used = 0;
	new_header->next_free = 0;
	i = 1;
	while (i < N_TNY_ALOCS_PER_PG)
	{
		new_header->next_free = new_header + TS_ALHEADR_SIZ + TNY_ALLOC_SIZE;
		new_header = new_header->next_free;
		new_header->used = 0;
		new_header->next_free = 0;
		++i;
	}
	info->tpages_tail = (struct s_tsPageHeader *)new_page;
	info->free_tallocs_tail = new_header;
	++info->ntpages;
}

/*
**	Divide up the page into individual allocation spaces each started by a
**	ts_Alloc_Header struct, and link the new page and spaces to the
**	global malloc struct.
*/

static void		add_small_page(void *new_page)
{
	struct s_tsAllocHeader	*new_header;
	unsigned int			i;

	if (!info->spages)
		info->spages = (struct s_tsPageHeader *)new_page;
	else
		info->spages_tail->next_page = (struct s_tsPageHeader *)new_page;
	new_header = (struct s_tsAllocHeader *)(new_page + SML_PG_OFSET);
	if (!info->free_sallocs)
		info->free_sallocs = new_header;
	else
		info->free_sallocs_tail->next_free = new_header;
	new_header->used = 0;
	new_header->next_free = 0;
	i = 1;
	while (i < N_SML_ALOCS_PER_PG)
	{
		new_header->next_free = new_header + TS_ALHEADR_SIZ + SML_ALLOC_SIZE;
		new_header = new_header->next_free;
		new_header->used = 0;
		new_header->next_free = 0;
		++i;
	}
	info->spages_tail = (struct s_tsPageHeader *)new_page;
	info->free_sallocs_tail = new_header;
	++info->nspages;
}

void		add_ts_page(unsigned int zone)
{
	void					*new_page;
	struct s_tsPageHeader	*new_pheader;

	new_page = mmap(0, info->pagesize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (!new_page)
		return ;
	new_pheader = (struct s_tsPageHeader *)new_page;
	new_pheader->nallocs = 0;
	new_pheader->next_page = 0;
	if (zone == TINY)
	{
		new_pheader->start_addr = new_page + TNY_PG_OFSET;
		add_tiny_page(new_page);
	}
	else
	{
		new_pheader->start_addr = new_page + SML_PG_OFSET;
		add_small_page(new_page);
	}
}

void		setup_malloc(void)
{
	void				*page;
	unsigned int		i;

	page = mmap(0, getpagesize(), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	info = (struct g_malloc *)page;
	info->pagesize = getpagesize();
	info->lallocs = 0;
	info->ntpages = 0;
	info->nspages = 0;
	i = 0;
	while (i < NPAGES_OVERHEAD)
	{
		add_ts_page(TINY);
		add_ts_page(SMALL);
		++i;
	}
}
