/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:51:42 by rreedy            #+#    #+#             */
/*   Updated: 2020/02/06 17:52:29 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "struct_tsAllocHeader.h"
#include "struct_lAllocHeader.h"
#include <stddef.h>

void			*ft_malloc(size_t size)
{
	void	*ptr;

	if (!malloc_info)
		setup_malloc();
	if (size <= TNY_ALOC_SIZ)
	{
		if (!malloc_info.free_talloc)
			make_ts_page(TINY);
		ptr = malloc_info->free_talloc;
		malloc_info->free_talloc = malloc_info->free_talloc_next;
		((struct s_tsAllocHeader)(ptr))->used = size;
	}
	else if (size <= SML_ALOC_SIZ)
	{
		if (!malloc_info.free_salloc)
			make_ts_page(SMALL);
		ptr = malloc_info->free_salloc;
		malloc_info->free_salloc = malloc_info->free_salloc_next;
		((struct s_tsAllocHeader)(ptr))->used = size;
	}
	else
		ptr = make_large_alloc(size);
	return (ptr);
}
