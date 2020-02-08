/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:51:42 by rreedy            #+#    #+#             */
/*   Updated: 2020/02/08 00:55:26 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "struct_tsAllocHeader.h"
#include "struct_lAllocHeader.h"
#include <stddef.h>

void			*malloc(size_t size)
{
	void	*ptr;

	if (!g_malloc)
		setup_malloc();
	if (size <= TNY_ALOC_SIZ)
	{
		if (!g_malloc->free_tallocs)
			make_ts_page(TINY);
		ptr = g_malloc->free_tallocs;
		g_malloc->free_tallocs = g_malloc->free_tallocs->next_free;
		((struct s_tsAllocHeader *)(ptr))->used = size;
	}
	else if (size <= SML_ALOC_SIZ)
	{
		if (!g_malloc->free_sallocs)
			make_ts_page(SMALL);
		ptr = g_malloc->free_sallocs;
		g_malloc->free_sallocs = g_malloc->free_sallocs->next_free;
		((struct s_tsAllocHeader *)(ptr))->used = size;
	}
	else
		ptr = make_large_alloc(size);
	return (ptr);
}
