/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:51:23 by rreedy            #+#    #+#             */
/*   Updated: 2020/02/06 17:51:34 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "struct_tsAllocHeader.h"
#include "struct_lAllocHeader.h"
#include <stddef.h>

void	*ft_realloc(void *ptr, size_t new_size)
{
	void			*new_ptr;
	void			*header;
	unsigned int	old_size;

	if (!ptr)
		return (malloc(new_size));
	new_ptr = 0;
	zone = find_header(ptr, header);
	old_size = (zone & (TINY | SMALL)) ? (struct s_tsAllocHeader)header->used :
			(struct s_lAllocHeader)header->used;
	if ((zone == TINY && new_size >= TINY_ALLOC_SiZE) ||
		(zone == SMALL && new_size >= SMALL_ALLOC_SiZE))
	{
		((struct s_tsAllocHeader)(header))->used = new_size;
		new_ptr = ptr;
	}
	else if (zone == LARGE && new_size >= LARGE_ALLOC_SiZE)
	{
		((struct s_lAllocHeader)(header))->used = new_size;
		new_ptr = ptr;
	}
	else if (zone)
	{
		new_ptr = malloc(new_size);
		ft_memcpy(newptr, ptr, old_size);
		ft_free(ptr);
	}
	return (new_ptr);
}
