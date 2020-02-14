/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:51:42 by rreedy            #+#    #+#             */
/*   Updated: 2020/02/14 04:59:57 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "new_pages.h"
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
			new_tspage(TINY);
		ptr = (void *)((uintptr_t)info->free_tallocs + info->ts_alheadr_siz);
		info->free_tallocs = info->free_tallocs->next_free;
		((struct s_tsAllocHeader *)(ptr))->used = size;
	}
	else if (size <= SML_ALLOC_SIZE)
	{
		if (!info->free_sallocs)
			new_tspage(SMALL);
		ptr = (void *)((uintptr_t)info->free_sallocs + info->ts_alheadr_siz);
		info->free_sallocs = info->free_sallocs->next_free;
		((struct s_tsAllocHeader *)(ptr))->used = size;
	}
	else
	{
		new_lpages(size);
		ptr = (void *)((uintptr_t)info->lallocs + info->lrg_alheadr_siz);
	}
	return (ptr);
}
