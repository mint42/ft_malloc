/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 18:47:57 by rreedy            #+#    #+#             */
/*   Updated: 2020/02/26 23:08:14 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

#include "global_struct_g_malloc.h"
#include <stddef.h>

/*
**	:)		CONFIGURE:
**
**	TNY_ALLOC_SIZ	-> size of a tiny allocation
**	SML_ALLOC_SIZ	-> size of a small allocation
**	NPAGES_OVRHEAD	-> How many pages of memory will be kept as a buffer
*/
# define TNY_ALLOC_SIZE 16
# define SML_ALLOC_SIZE 1024
# define TNY_PAGES_OVERHEAD 2
# define SML_PAGES_OVERHEAD 34

/*
**	>:(		DO NOT CONFIGURE:
*/
# define TINY 1
# define SMALL 2
# define LARGE 3

struct g_malloc	*info;

void			*malloc(size_t size);
void			*calloc(size_t num, size_t size);
void			*realloc(void *ptr, size_t size);
void			free(void *ptr);

/*
**	Manage Malloc
*/

void			setup_malloc(void);
void			new_tspage(unsigned int zone);
void			new_lpages(size_t used_size);
unsigned int	find_header(void *ptr, void **header);

#endif
