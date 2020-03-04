/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_pages.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 22:09:17 by rreedy            #+#    #+#             */
/*   Updated: 2020/03/04 15:42:44 by rreedy           ###   ########.fr       */
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

void		new_lrg_mmap(size_t used_size)
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

/*
**	Divide up the page into individual allocation spaces each started by a
**	ts_Alloc_Header struct, and link the new page and spaces to the
**	global malloc struct.
*/

void		new_sml_mmap(void)
{
	void					*new_mmap;
	struct s_tsPageHeader	*new_pheader;
	struct s_tsAllocHeader	*new_alheader;
	unsigned int			i;

	new_mmap = mmap(0, info->sml_mmap_size, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANON, -1, 0);
	if (!new_mmap)
		return ;
	new_pheader = (struct s_tsPageHeader *)new_mmap;
	new_pheader->nallocs = 0;
	new_pheader->next_mmap = 0;
	if (!info->smmaps)
		info->smmaps = (struct s_tsPageHeader *)new_mmap;
	else
		info->smmaps_tail->next_mmap = (struct s_tsPageHeader *)new_mmap;
	new_alheader = (struct s_tsAllocHeader *)((uintptr_t)new_mmap + info->sml_mmap_offset);
	if (!info->free_sallocs)
		info->free_sallocs = new_alheader;
	else
		info->free_sallocs_tail->next_free = new_alheader;
	new_alheader->free = 1;
	new_alheader->used = 0;
	new_alheader->id = 0;
	new_alheader->next_free = 0;
	i = 1;
	while (i < info->n_sml_alocs_per_mmap)
	{
		new_alheader->next_free = (struct s_tsAllocHeader *)((uintptr_t)new_alheader + info->ts_alheadr_siz + SML_ALLOC_SIZE);
		new_alheader = new_alheader->next_free;
		new_alheader->free = 1;
		new_alheader->used = 0;
		new_alheader->id = i;
		new_alheader->next_free = 0;
		++i;
	}
	info->smmaps_tail = (struct s_tsPageHeader *)new_mmap;
	info->free_sallocs_tail = new_alheader;
	++info->nsmmaps;
}

void		new_tny_mmap(void)
{
	void					*new_mmap;
	struct s_tsPageHeader	*new_pheader;
	struct s_tsAllocHeader	*new_alheader;
	unsigned int			i;

	new_mmap = mmap(0, info->tny_mmap_size, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANON, -1, 0);
	if (!new_mmap)
		return ;
	new_pheader = (struct s_tsPageHeader *)new_mmap;
	new_pheader->nallocs = 0;
	new_pheader->next_mmap = 0;
	if (!info->tmmaps)
		info->tmmaps = (struct s_tsPageHeader *)new_mmap;
	else
		info->tmmaps_tail->next_mmap = (struct s_tsPageHeader *)new_mmap;
	new_alheader = (struct s_tsAllocHeader *)((uintptr_t)new_mmap + info->tny_mmap_offset);
	if (!info->free_tallocs)
		info->free_tallocs = new_alheader;
	else
		info->free_tallocs_tail->next_free = new_alheader;
	new_alheader->free = 1;
	new_alheader->used = 0;
	new_alheader->id = 0;
	new_alheader->next_free = 0;
	i = 1;
	while (i < info->n_tny_alocs_per_mmap)
	{
		new_alheader->next_free = (struct s_tsAllocHeader *)((uintptr_t)new_alheader + info->ts_alheadr_siz + TNY_ALLOC_SIZE);
		new_alheader = new_alheader->next_free;
		new_alheader->free = 1;
		new_alheader->used = 0;
		new_alheader->id = i;
		new_alheader->next_free = 0;
		++i;
	}
	info->tmmaps_tail = (struct s_tsPageHeader *)new_mmap;
	info->free_tallocs_tail = new_alheader;
	++info->ntmmaps;
}
