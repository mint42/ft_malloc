/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 04:30:39 by rreedy            #+#    #+#             */
/*   Updated: 2020/02/09 04:31:18 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	zero_mem(void *ptr, size_t size)
{
	unsigned long int	*fast_cur;
	unsigned long int	zero;
	unsigned char		*slow_cur;
	unsigned char		sizeoflong;

	sizeoflong = sizeof(unsigned long int);
	fast_cur = (unsigned long int *)ptr;
	zero = 0;
	while (size >= sizeoflong)
	{
		*fast_cur = zero;
		++fast_cur;
		ptr = ptr + sizeoflong;
		size = size - sizeoflong;
	}
	slow_cur = (unsigned char *)fast_cur;
	while (size > 0)
	{
		*slow_cur = (unsigned char)zero;
		++slow_cur;
		++ptr;
		--size;
	}
}

void	cpy_mem(void *newptr, void *ptr, size_t size)
{
	unsigned long int	*fast_cur;
	unsigned char		*slow_cur;
	unsigned char		sizeoflong;

	sizeoflong = sizeof(unsigned long int);
	fast_cur = (unsigned long int *)newptr;
	while (size >= sizeoflong)
	{
		*fast_cur = *(unsigned long int *)ptr;
		++fast_cur;
		ptr = ptr + sizeoflong;
		size = size - sizeoflong;
	}
	slow_cur = (unsigned char *)fast_cur;
	while (size > 0)
	{
		*slow_cur = *(unsigned char *)ptr;
		++slow_cur;
		++ptr;
		--size;
	}
}
