/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_malloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:38:09 by rreedy            #+#    #+#             */
/*   Updated: 2020/03/02 20:51:09 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "mmaps.h"
#include "struct_tsPageHeader.h"
#include "struct_tsAllocHeader.h"
#include "struct_lAllocHeader.h"
#include <sys/mman.h>
#include <stddef.h>
#include <unistd.h>

static void		setup_alignment(void)
{
	info->lrg_alheadr_siz = sizeof(struct s_lAllocHeader);
	info->ts_alheadr_siz = sizeof(struct s_tsAllocHeader);
	info->ts_pgheadr_siz = sizeof(struct s_tsPageHeader);
	info->pagesize = getpagesize();
	info->tny_mmap_size = info->pagesize * TNY_OVERHEAD;
	info->sml_mmap_size = info->pagesize * SML_OVERHEAD;
	info->tny_mmap_pad = ((info->tny_mmap_size - info->ts_pgheadr_siz) %
			(info->ts_alheadr_siz + TNY_ALLOC_SIZE));
	info->sml_mmap_pad = ((info->sml_mmap_size - info->ts_pgheadr_siz) %
			(info->ts_alheadr_siz + SML_ALLOC_SIZE));
	info->tny_mmap_offset = info->ts_pgheadr_siz + info->tny_mmap_pad;
	info->sml_mmap_offset = info->ts_pgheadr_siz + info->sml_mmap_pad;
	info->tny_mmap_space = info->tny_mmap_size - info->tny_mmap_offset;
	info->sml_mmap_space = info->sml_mmap_size - info->sml_mmap_offset;
	info->n_tny_alocs_per_mmap = info->tny_mmap_space /
			(info->ts_alheadr_siz + TNY_ALLOC_SIZE);
	info->n_sml_alocs_per_mmap = info->sml_mmap_space /
			(info->ts_alheadr_siz + SML_ALLOC_SIZE);
}

void			setup_malloc(void)
{
	void				*page;

	page = mmap(0, getpagesize(), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	info = (struct g_malloc *)page;
	setup_alignment();
	info->lallocs = 0;
	info->ntmmaps = 0;
	info->nsmmaps = 0;
	new_tny_mmap();
	new_sml_mmap();
}
