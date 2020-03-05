/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:51:42 by rreedy            #+#    #+#             */
/*   Updated: 2020/03/04 20:08:42 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "mmaps.h"
#include "struct_tnysml_mmap_header.h"
#include "struct_tnysml_alloc_header.h"
#include <unistd.h>

static void		*malloc_tny(size_t size)
{
	void	*ptr;

	if (!info->free_tny_allocs)
		new_tny_mmap();
	ptr = (void *)info->free_tny_allocs;
	((struct s_tnysml_alloc_header *)(ptr))->free = 0;
	((struct s_tnysml_alloc_header *)(ptr))->used = size;
	ptr = (void *)((uintptr_t)ptr + info->tnysml_alheadr_siz);
	info->free_tny_allocs = info->free_tny_allocs->next_free;
	return (ptr);
}

static void		*malloc_sml(size_t size)
{
	void	*ptr;

	if (!info->free_sml_allocs)
		new_sml_mmap();
	ptr = (void *)info->free_sml_allocs;
	((struct s_tnysml_alloc_header *)(ptr))->free = 0;
	((struct s_tnysml_alloc_header *)(ptr))->used = size;
	ptr = (void *)((uintptr_t)ptr + info->tnysml_alheadr_siz);
	info->free_sml_allocs = info->free_sml_allocs->next_free;
	return (ptr);
}

void			*malloc(size_t size)
{
	void	*ptr;

	if (!info)
		setup_malloc();
	if (size <= TNY_ALLOC_SIZE)
		ptr = malloc_tny(size);
	else if (size <= SML_ALLOC_SIZE)
		ptr = malloc_sml(size);
	else
	{
		new_lrg_mmap(size);
		ptr = (void *)((uintptr_t)info->lrg_allocs + info->lrg_alheadr_siz);
	}
	return (ptr);
}
