/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_malloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:38:09 by rreedy            #+#    #+#             */
/*   Updated: 2020/03/02 18:40:56 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "new_pages.h"
#include "struct_tsPageHeader.h"
#include "struct_tsAllocHeader.h"
#include "struct_lAllocHeader.h"
#include <sys/mman.h>
#include <stddef.h>
#include <unistd.h>

static void		setup_alignment(void)
{
	info->pagesize = getpagesize();
	info->lrg_alheadr_siz = sizeof(struct s_lAllocHeader);
	info->ts_alheadr_siz = sizeof(struct s_tsAllocHeader);
	info->ts_pgheadr_siz = sizeof(struct s_tsPageHeader);
	info->tny_pg_pad = ((info->pagesize - info->ts_pgheadr_siz) % (info->ts_alheadr_siz + TNY_ALLOC_SIZE));
	info->sml_pg_pad = ((info->pagesize - info->ts_pgheadr_siz) % (info->ts_alheadr_siz + SML_ALLOC_SIZE));
	info->tny_pg_offset = (info->ts_pgheadr_siz + info->tny_pg_pad);
	info->sml_pg_offset = (info->ts_pgheadr_siz + info->sml_pg_pad);
	info->tny_pg_space = (info->pagesize - info->tny_pg_offset);
	info->sml_pg_space = (info->pagesize - info->sml_pg_offset);
	info->n_tny_alocs_per_pg = (info->tny_pg_space / (info->ts_alheadr_siz + TNY_ALLOC_SIZE));
	info->n_sml_alocs_per_pg = (info->sml_pg_space / (info->ts_alheadr_siz + SML_ALLOC_SIZE));
}

void			setup_malloc(void)
{
	void				*page;
	unsigned int		i;

	page = mmap(0, getpagesize(), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	info = (struct g_malloc *)page;
	setup_alignment();
	info->lallocs = 0;
	info->ntpages = 0;
	info->nspages = 0;
	i = 0;
	while (i < TNY_PAGES_OVERHEAD)
	{
		new_tspages(TINY);
		++i;
	}
	i = 0;
	while (i < SML_PAGES_OVERHEAD)
	{
		new_tspages(SMALL);
		++i;
	}
}
