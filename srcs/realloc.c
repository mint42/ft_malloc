/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:51:23 by rreedy            #+#    #+#             */
/*   Updated: 2020/02/07 07:54:40 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
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

	if (!ptr)
		return (malloc(new_size));
	new_ptr = 0;
	header = 0;
	zone = find_header(ptr, header);
	if ((zone == TINY && new_size >= TNY_ALOC_SIZ) ||
		(zone == SMALL && new_size >= SML_ALOC_SIZ))
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
		old_size = (zone & (TINY | SMALL)) ? ((struct s_tsAllocHeader *)(header))->used :
				((struct s_lAllocHeader *)(header))->used;
		cpy_mem(new_ptr, ptr, old_size);
		free(ptr);
	}
	return (new_ptr);
}
