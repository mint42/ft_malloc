/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:51:42 by rreedy            #+#    #+#             */
/*   Updated: 2020/03/02 20:54:34 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "mmaps.h"
#include "struct_tsAllocHeader.h"
#include "struct_lAllocHeader.h"
#include <stddef.h>
#include <unistd.h>

void			*malloc(size_t size)
{
	void	*ptr;

	if (!info)
		setup_malloc();
	if (size <= TNY_ALLOC_SIZE)
	{
		if (!info->free_tallocs)
			new_tny_mmap();
		ptr = (void *)info->free_tallocs;
		((struct s_tsAllocHeader *)(ptr))->free = 0;
		((struct s_tsAllocHeader *)(ptr))->used = size;
		ptr = (void *)((uintptr_t)ptr + info->ts_alheadr_siz);
		info->free_tallocs = info->free_tallocs->next_free;
	}
	else if (size <= SML_ALLOC_SIZE)
	{
		if (!info->free_sallocs)
			new_sml_mmap();
		ptr = (void *)info->free_sallocs;
		((struct s_tsAllocHeader *)(ptr))->free = 0;
		((struct s_tsAllocHeader *)(ptr))->used = size;
		ptr = (void *)((uintptr_t)ptr + info->ts_alheadr_siz);
		info->free_sallocs = info->free_sallocs->next_free;
	}
	else
	{
		new_lrg_mmap(size);
		ptr = (void *)((uintptr_t)info->lallocs + info->lrg_alheadr_siz);
	}
	return (ptr);
}
