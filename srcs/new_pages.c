/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_pages.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 22:09:17 by rreedy            #+#    #+#             */
/*   Updated: 2020/02/26 17:48:17 by rreedy           ###   ########.fr       */
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

void		new_lpages(size_t used_size)
{
	struct s_lAllocHeader	*new_header;
	void					*new_alloc;
	size_t					size;

	size = ((used_size / info->pagesize) + 1) * info->pagesize;
	new_alloc = mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (!new_alloc)
		return ;
	new_header = (struct s_lAllocHeader *)new_alloc;
	new_header->size = size;
	new_header->used = used_size;
	new_header->prev_alloc = 0;
	new_header->next_alloc = 0;
	if (info->lallocs)
	{
		info->lallocs->prev_alloc = new_header;
		new_header->next_alloc = info->lallocs;
	}
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
	new_header = (struct s_tsAllocHeader *)((uintptr_t)new_page + info->tny_pg_offset);
	if (!info->free_tallocs)
		info->free_tallocs = new_header;
	else
		info->free_tallocs_tail->next_free = new_header;
	new_header->free = 1;
	new_header->used = 0;
	new_header->next_free = 0;
	i = 1;
	while (i < info->n_tny_alocs_per_pg)
	{
		new_header->next_free = (struct s_tsAllocHeader *)((uintptr_t)new_header + info->ts_alheadr_siz + TNY_ALLOC_SIZE);
		new_header = new_header->next_free;
		new_header->free = 1;
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
	new_header = (struct s_tsAllocHeader *)((uintptr_t)new_page + info->sml_pg_offset);
	if (!info->free_sallocs)
		info->free_sallocs = new_header;
	else
		info->free_sallocs_tail->next_free = new_header;
	new_header->free = 1;
	new_header->used = 0;
	new_header->next_free = 0;
	i = 1;
	while (i < info->n_sml_alocs_per_pg)
	{
		new_header->next_free = (struct s_tsAllocHeader *)((uintptr_t)new_header + info->ts_alheadr_siz + SML_ALLOC_SIZE);
		new_header = new_header->next_free;
		new_header->free = 1;
		new_header->used = 0;
		new_header->next_free = 0;
		++i;
	}
	info->spages_tail = (struct s_tsPageHeader *)new_page;
	info->free_sallocs_tail = new_header;
	++info->nspages;
}

void		new_tspage(unsigned int zone)
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
		add_tiny_page(new_page);
	else
		add_small_page(new_page);
}
