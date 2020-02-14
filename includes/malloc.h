/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 18:47:57 by rreedy            #+#    #+#             */
/*   Updated: 2020/02/14 06:11:36 by rreedy           ###   ########.fr       */
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
# define SML_ALLOC_SIZE 512
# define NPAGES_OVERHEAD 3

/*
**	>:(		DO NOT CONFIGURE:
**
**	*_PG_PAD	-> Padding will be needed to align the allocations evenly
**	*_PG_SPACE	-> How much of the page is free for the allocations considering
**                 getpagesize(), the tiny/small page header size, and padding
*/
# define PAGESIZE 4096
# define TNY_PG_PAD ((PAGESIZE - TS_PGHEADR_SIZ) % (TNY_ALLOC_SIZE + TS_ALHEADR_SIZ))
# define SML_PG_PAD ((PAGESIZE - TS_PGHEADR_SIZ) % (SML_ALLOC_SIZE + TS_ALHEADR_SIZ))
# define TNY_PG_OFSET (TS_PGHEADR_SIZ + TNY_PG_PAD)
# define SML_PG_OFSET (TS_PGHEADR_SIZ + SML_PG_PAD)
# define TNY_PG_SPACE (PAGESIZE - TNY_PG_OFSET)
# define SML_PG_SPACE (PAGESIZE - SML_PG_OFSET)
# define N_TNY_ALOCS_PER_PG (TNY_PG_SPACE / (TS_ALHEADR_SIZ + TNY_ALLOC_SIZE))
# define N_SML_ALOCS_PER_PG (SML_PG_SPACE / (TS_ALHEADR_SIZ + SML_ALLOC_SIZE))
# define TINY 1
# define SMALL 2
# define LARGE 3

struct g_malloc	*info;

void			*malloc(size_t size);
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
