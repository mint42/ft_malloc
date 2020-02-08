/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_malloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:38:09 by rreedy            #+#    #+#             */
/*   Updated: 2020/02/08 00:59:01 by rreedy           ###   ########.fr       */
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

void		*make_large_alloc(size_t used_size)
{
	struct s_lAllocHeader	*new_header;
	void					*new_alloc;

	new_header = 0;
	new_header->used = used_size;
	new_header->size = (used_size / g_malloc->pagesize) + g_malloc->pagesize;
	new_alloc = mmap(0, new_header->size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, new_header->size);
	if (!new_alloc)
		return (0);
	new_header->start_addr = new_alloc + LRG_ALOC_HEADR_SIZ;
	cpy_mem(new_alloc, new_header, LRG_ALOC_HEADR_SIZ);
	new_header->prev_alloc = g_malloc->lallocs_tail->next_alloc;
	new_header->next_alloc = 0;
	return (new_alloc);
}

static void			fill_tiny_page(void *new_page)
{
	struct s_tsAllocHeader	*new_aheader;
	void					*cur;
	unsigned int			i;

	cur = new_page;
	new_aheader = (struct s_tsAllocHeader *)cur;
	new_aheader->used = 0;
	new_aheader->next_free = 0;
	cur = cur + TS_ALOC_HEADR_SIZ + TNY_ALOC_SIZ;
	i = N_TNY_ALOCS_PER_PG - 1;
	while (i > 0)
	{
		new_aheader->next_free = cur;
		new_aheader = (struct s_tsAllocHeader *)cur;
		new_aheader->used = 0;
		new_aheader->next_free = 0;
		g_malloc->free_tallocs_tail->next_free = new_aheader;
		g_malloc->free_tallocs_tail = g_malloc->free_tallocs_tail->next_free;
		cur = cur + TS_ALOC_HEADR_SIZ + TNY_ALOC_SIZ;
		--i;
	}
	g_malloc->tpages_tail->next_page = new_page;
	g_malloc->tpages_tail = g_malloc->tpages_tail->next_page;
	++g_malloc->tpages;
}

static void		fill_small_page(void *new_page)
{
	struct s_tsAllocHeader	*new_aheader;
	void					*cur;
	unsigned int			i;

	cur = new_page;
	new_aheader = (struct s_tsAllocHeader *)cur;
	new_aheader->used = 0;
	new_aheader->next_free = 0;
	cur = cur + TS_ALOC_HEADR_SIZ + SML_ALOC_SIZ;
	i = N_SML_ALOCS_PER_PG - 1;
	while (i > 0)
	{
		new_aheader->next_free = cur;
		new_aheader = (struct s_tsAllocHeader *)cur;
		new_aheader->used = 0;
		new_aheader->next_free = 0;
		g_malloc->free_sallocs_tail->next_free = new_aheader;
		g_malloc->free_sallocs_tail = g_malloc->free_sallocs_tail->next_free;
		cur = cur + TS_ALOC_HEADR_SIZ + SML_ALOC_SIZ;
		--i;
	}
	g_malloc->spages_tail->next_page = new_page;
	g_malloc->spages_tail = g_malloc->spages_tail->next_page;
	++g_malloc->spages;
}

void			*make_ts_page(unsigned int zone)
{
	void					*new_page;
	struct s_tsPageHeader	*new_pheader;

	new_page = mmap(0, g_malloc->pagesize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, g_malloc->pagesize);
	if (!new_page)
		return (0);
	new_pheader = (struct s_tsPageHeader *)new_page;
	new_pheader->nallocs = 0;
	new_pheader->next_page = 0;
	if (zone == TINY)
	{
		new_pheader->start_addr = new_page +
				TS_PG_HEADR_SIZ + TNY_PG_PAD + TS_ALOC_HEADR_SIZ;
		fill_tiny_page(new_page);
	}
	else
	{
		new_pheader->start_addr = new_page + TS_PG_HEADR_SIZ + SML_PG_PAD + TS_ALOC_HEADR_SIZ;
		fill_small_page(new_page);
	}
	return (new_page);
}

void		setup_malloc(void)
{
	unsigned int	i;

	i = NPAGES_OVERHEAD;
	while (i > 0)
	{
		make_ts_page(TINY);
		--i;
	}
	while (i > 0)
	{
		make_ts_page(SMALL);
		--i;
	}
	g_malloc->pagesize = getpagesize();
	g_malloc->lallocs = 0;
	g_malloc->lallocs_tail = 0;
	g_malloc->ntpages = NPAGES_OVERHEAD;
	g_malloc->nspages = NPAGES_OVERHEAD;
}
