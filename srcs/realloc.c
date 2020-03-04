/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:51:23 by rreedy            #+#    #+#             */
/*   Updated: 2020/03/04 15:33:40 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "find_header.h"
#include "mem.h"
#include "struct_tsAllocHeader.h"
#include "struct_lAllocHeader.h"
#include <stddef.h>

void	*realloc(void *ptr, size_t new_size)
{
	void			*new_ptr;
	void			*header;
	unsigned int	old_size;
	unsigned char	zone;

	if (!info)
		setup_malloc();
	if (!ptr)
	{
		ptr = malloc(new_size);
		return (ptr);
	}
	new_ptr = 0;
	zone = find_header(ptr, &header);
	if ((zone == TINY && new_size <= TNY_ALLOC_SIZE) || (zone == SMALL && new_size > TNY_ALLOC_SIZE && new_size <= SML_ALLOC_SIZE))
	{
		((struct s_tsAllocHeader *)(header))->used = new_size;
		new_ptr = ptr;
	}
	else if (zone == LARGE && new_size <= ((struct s_lAllocHeader *)(header))->size)
	{
		((struct s_lAllocHeader *)(header))->used = new_size;
		new_ptr = ptr;
	}
	else if (zone)
	{
		new_ptr = malloc(new_size);
		if (zone & (TINY | SMALL))
			old_size = ((struct s_tsAllocHeader *)(header))->used;
		else
			old_size = ((struct s_lAllocHeader *)(header))->used;
		cpy_mem(new_ptr, ptr, ((old_size < new_size) ? old_size : new_size));
		free(ptr);
	}
	return (new_ptr);
}
