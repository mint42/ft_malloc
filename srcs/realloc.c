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
#include "struct_tsAllocHeader.h"
#include "struct_lAllocHeader.h"
#include <stddef.h>

void	cpy_memory(void *newptr, void *ptr, size_t size)
{
	unsigned long int	*fast_cur;
	unsigned char		*slow_cur;
	unsigned char		sizeoflong;

	sizeoflong = sizeof(unsigned long int);
	fast_cur = (unsigned long int *)newptr;
	while (size > sizeoflong)
	{
		*fast_cur = *(unsigned long int *)ptr;
		fast_cur = fast_cur + sizeoflong;
		src = src + sizeoflong;
		size = size - sizeoflong;
	}
	slow_cur = (unsigned char *)fast_cur;
	while (size > 0)
	{
		*slow_cur = *(unsigned char *)src;
		++slow_cur;
		++src;
		--size;
	}
}

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
		cpy_memory(newptr, ptr, old_size);
		ft_free(ptr);
	}
	return (new_ptr);
}
