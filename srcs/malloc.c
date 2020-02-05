/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 00:36:23 by rreedy            #+#    #+#             */
/*   Updated: 2020/02/02 06:29:13 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "ft_printf.h"
#include <stddef.h>
#include <stdlib.h>

void	*ft_malloc(size_t size)
{
	void	*ptr;

	if (size <= TINY_ALLOC_SIZE)
	{
		if (!malloc_info.free_talloc)
			make_new_page(TINY_ALLOC_SIZE);
		ptr = dequeue(malloc_info.free_talloc);
	}
	else if (size <= SMALL_ALLOC_SIZE)
	{
		if (!malloc_info.free_salloc)
			make_new_page(SMALL_ALLOC_SIZE);
		ptr = dequeue(malloc_info.free_salloc);
	}
	else
		ptr = make_large_alloc(size);
	return (ptr);
}

void	*ft_realloc(void *ptr, size_t new_size)
{
	void		*new_ptr;
	void		*header;

	ptr = find_alloc(ptr);
	if (new_size <= node.size)
		return (ptr);
	new_ptr = malloc(new_size);
	ft_memcpy(newptr, ptr, node.size);
	free(ptr);
	return (new_ptr);
}

void	ft_free(void *ptr)
{
	s_local		*node;

	node = find_alloc(ptr);
	free(node);
}

int		main()
{
	void	*ptr;
	size_t	size;

	ptr = 0;
	size = 0;
	ft_malloc(size);
	ft_realloc(ptr, size);
	ft_free(ptr);
	return (0);
}

//int		main()
//{
//	void	*ptr;
//	size_t	size;
//
//	ptr = 0;
//	size = 0;
//	ft_printf("%p\n", ptr);
//	ptr = malloc(size);
//	ft_printf("%p\n", ptr);
//	return (0);
//}
