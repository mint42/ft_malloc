/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_malloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:38:09 by rreedy            #+#    #+#             */
/*   Updated: 2020/02/06 17:53:27 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "struct_tsPageHeader.h"
#include "struct_tsAllocHeader.h"
#include "struct_lAllocHeader.h"
#include <stddef.h>

void		*make_large_alloc(size_t used_size)
{
	struct s_lAllocHeader	*new_header;
	void					*new_alloc;

	new_header->used = used_size;
	new_header->size = (used_size / g_malloc->pagesize) + g_malloc->pagesize;
	new_alloc = mmap(new_header.size);
	if (!new_alloc)
		return (0);
	new_header->start_addr = new_alloc + LRG_ALOC_HEADR_SIZ;
	ft_memcpy(new_alloc, new_header);
	new_header->prev_alloc = g_malloc.lAlloc_tail->next_alloc;
	new_header->next_alloc = 0;
	return (new_alloc);
}

static void			fill_tiny_page(void *new_page)
{
	struct s_tsPageHeader	*new_aheader;
	void					*cur;
	unsigned int			i;

	new_aheader = (struct s_tsAllocHeader)cur;
	new_aheader->used = 0;
	new_aheader->next = 0;
	cur = cur + TS_ALOC_HEADR_SIZ + TNY_ALOC_SIZ;
	i = N_TNY_ALOCS_PER_PG - 1;
	while (i > 0)
	{
		new_aheader->next_free = cur;
		new_aheader = (struct s_tsAllocHeader)cur;
		new_aheader->used = 0;
		new_aheader->next = 0;
		g_malloc->free_tallocs_tail->next = new_aheader;
		g_malloc->free_tallocs_tail = g_malloc->free_tallocs_tail->next;
		cur = cur + TS_ALOC_HEADR_SIZ + TNY_ALOC_SIZ;
		--i;
	}
	g_malloc->tpages_tail->next = new_page;
	g_malloc->tpages_tail = g_malloc->tpages_tail->next;
	++g_malloc->tpages;
}

static void		fill_small_page(void *new_page)
{
	struct s_tsPageHeader	*new_aheader;
	void					*cur;
	unsigned int			i;

	new_aheader = (struct s_tsAllocHeader)cur;
	new_aheader->used = 0;
	new_aheader->next = 0;
	cur = cur + TS_ALOC_HEADR_SIZ + SML_ALOC_SIZ;
	i = N_SML_ALOCS_PER_PG - 1;
	while (i > 0)
	{
		new_aheader->next_free = cur;
		new_aheader = (struct s_tsAllocHeader)cur;
		new_aheader->used = 0;
		new_aheader->next = 0;
		g_malloc->free_sallocs_tail->next = new_aheader;
		g_malloc->free_sallocs_tail = g_malloc->free_sallocs_tail->next;
		cur = cur + TS_ALOC_HEADR_SIZ + SML_ALOC_SIZ;
		--i;
	}
	g_malloc->spages_tail->next = new_page;
	g_malloc->spages_tail = g_malloc->spages_tail->next;
	++g_malloc->spages;
}

void			*make_ts_page(unsigned int zone)
{
	void					*new_page;
	struct s_tsPageHeader	*new_pheader;

	new_page = mmap(g_malloc->pagesize);
	if (!new_page)
		return (0);
	new_pheader = (struct s_tsPageHeader)new_page;
	new_pheader->nfree = 0;
	new_pheader->next_page = 0;
	if (zone == TINY)
	{
		new_pheader->start_addr = new_page +
				TS_PG_HEADR_SIZE + TNY_PG_PAD + TS_ALOC_HEADR_SIZ;
		fill_tiny_page(new_page);
	{
	else
	{
		new_pheader->start_addr = new_page +
				TS_PG_HEADR_SIZE + SML_PG_PAD + TS_ALOC_HEADR_SIZ;
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
