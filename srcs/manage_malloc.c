/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_malloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:38:09 by rreedy            #+#    #+#             */
/*   Updated: 2020/02/08 16:27:57 by rreedy           ###   ########.fr       */
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

	size = (used_size / g_malloc->pagesize) + g_malloc->pagesize;
	new_alloc = mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (!new_alloc)
		return ;
	new_header = (struct s_lAllocHeader *)new_alloc;
	new_header->size = size;
	new_header->used = used_size;
	new_header->start_addr = new_alloc + LRG_ALOC_HEADR_SIZ;
	new_header->prev_alloc = 0;
	new_header->next_alloc = g_malloc->lallocs;
	g_malloc->lallocs->prev_alloc = new_header;
	g_malloc->lallocs = new_header;
}

static void			add_tiny_page(void *new_page)
{
	struct s_tsAllocHeader	*new_header;
	unsigned int			i;

	if (N_TNY_ALOCS_PER_PG <= 0)
		return ;
	new_header = (struct s_tsAllocHeader *)new_page;
	new_header->used = 0;
	new_header->next_free = 0;
	g_malloc->free_tallocs_tail->next_free = new_header;
	i = 1;
	while (i < N_TNY_ALOCS_PER_PG)
	{
		new_header->next_free = new_header + TS_ALOC_HEADR_SIZ + TNY_ALOC_SIZ;
		new_header = new_header->next_free;
		new_header->used = 0;
		new_header->next_free = 0;
		++i;
	}
	g_malloc->free_tallocs_tail = new_header;
	g_malloc->tpages_tail->next_page = new_page;
	g_malloc->tpages_tail = g_malloc->tpages_tail->next_page;
	++g_malloc->ntpages;
}

static void		add_small_page(void *new_page)
{
	struct s_tsAllocHeader	*new_header;
	unsigned int			i;

	if (!g_malloc->spages)
		g_malloc->spages = new_page;
	else
		g_malloc->spages_tail->next_page = new_page;
	g_malloc->spages_tail = new_page;
	new_header = (struct s_tsAllocHeader *)new_page;
	new_header->used = 0;
	new_header->next_free = 0;
	if (!g_malloc->free_sallocs)
		g_malloc->free_sallocs = new_header;
	else
		g_malloc->free_sallocs_tail->next_free = new_header;
	i = 1;
	while (i < N_SML_ALOCS_PER_PG)
	{
		new_header->next_free = new_header + TS_ALOC_HEADR_SIZ + SML_ALOC_SIZ;
		new_header = new_header->next_free;
		new_header->used = 0;
		new_header->next_free = 0;
		++i;
	}
	g_malloc->free_sallocs_tail = new_header;
	++g_malloc->nspages;
}

void		add_ts_page(unsigned int zone)
{
	void					*new_page;
	struct s_tsPageHeader	*new_pheader;

	new_page = mmap(0, g_malloc->pagesize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (!new_page)
		return ;
	new_pheader = (struct s_tsPageHeader *)new_page;
	new_pheader->start_addr = new_page + TS_PG_HEADR_SIZ + TS_ALOC_HEADR_SIZ;
	new_pheader->nallocs = 0;
	new_pheader->next_page = 0;
	if (zone == TINY)
	{
		new_pheader->start_addr += TNY_PG_PAD;
		add_tiny_page(new_page);
	}
	else
	{
		new_pheader->start_addr += SML_PG_PAD;
		add_small_page(new_page);
	}
}

void		setup_malloc(void)
{
	void				*page;
	unsigned int		i;

	page = mmap(0, getpagesize(), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	g_malloc = (struct g_malloc *)page;
	g_malloc->pagesize = getpagesize();
	g_malloc->lallocs = 0;
	g_malloc->ntpages = 0;
	g_malloc->nspages = 0;
	i = 0;
	while (i < NPAGES_OVERHEAD)
	{
		add_ts_page(TINY);
		add_ts_page(SMALL);
		++i;
	}
}
