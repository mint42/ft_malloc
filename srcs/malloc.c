/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:51:42 by rreedy            #+#    #+#             */
/*   Updated: 2020/02/09 01:37:43 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "struct_tsAllocHeader.h"
#include "struct_lAllocHeader.h"
#include <stddef.h>

void			*malloc(size_t size)
{
	void	*ptr;

	if (!info)
		setup_malloc();
	if (size <= TNY_ALLOC_SIZE)
	{
		if (!info->free_tallocs)
			add_ts_page(TINY);
		ptr = info->free_tallocs;
		info->free_tallocs = info->free_tallocs->next_free;
		((struct s_tsAllocHeader *)(ptr))->used = size;
	}
	else if (size <= SML_ALLOC_SIZE)
	{
		if (!info->free_sallocs)
			add_ts_page(SMALL);
		ptr = info->free_sallocs;
		info->free_sallocs = info->free_sallocs->next_free;
		((struct s_tsAllocHeader *)(ptr))->used = size;
	}
	else
	{
		add_large_alloc(size);
		ptr = info->lallocs;
	}
	return (ptr);
}
