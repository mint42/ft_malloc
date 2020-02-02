/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 00:36:23 by rreedy            #+#    #+#             */
/*   Updated: 2020/02/02 00:36:40 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include "ft_printf.h"
#include <stddef.h>

void	*malloc(size_t size)
{
	void	*ptr;

	ptr = 0;
	(void)size;
	ft_printf("called malloc()\n");
	return (ptr);
}

void	*realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	new_ptr = 0;
	(void)ptr;
	(void)size;
	ft_printf("called realloc()\n");
	return (new_ptr);
}

void	free(void *ptr)
{
	(void)ptr;
	ft_printf("called free()\n");
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
