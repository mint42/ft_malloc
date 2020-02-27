/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 16:23:02 by rreedy            #+#    #+#             */
/*   Updated: 2020/02/26 17:52:46 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "mem.h"

void			*calloc(size_t num, size_t size)
{
	void	*ptr;

	if (!num || !size)
		return (0);
	ptr = malloc(num * size);
	if (ptr)
		zero_mem(ptr, num * size);
	return (ptr);
}
