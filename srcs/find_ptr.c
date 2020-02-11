/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ptr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:22:23 by rreedy            #+#    #+#             */
/*   Updated: 2020/02/10 17:11:58 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "struct_tsPageHeader.h"
#include "struct_tsAllocHeader.h"
#include "struct_lAllocHeader.h"
#include <stddef.h>
#include <unistd.h>

// TODO: consider when trying to access pointer that is inside of a header??

static void		*check_tiny(void *ptr)
{
	struct s_tsPageHeader	*cur;

	cur = info->tpages;
	while (cur)
	{
		if ((uintptr_t)ptr >= (uintptr_t)cur + TNY_PG_OFSET && (uintptr_t)ptr <= (uintptr_t)cur + PAGESIZE && ((uintptr_t)ptr - (uintptr_t)cur) %				TNY_ALLOC_SIZE >= TS_ALHEADR_SIZ)
			return ((void *)((uintptr_t)ptr - ((TNY_ALLOC_SIZE % (uintptr_t)ptr) - TS_ALHEADR_SIZ)));
		cur = cur->next_page;
	}
	return (0);
}

static void		*check_small(void *ptr)
{
	struct s_tsPageHeader	*cur;

	cur = info->tpages;
	while (cur)
	{
		if ((uintptr_t)ptr >= (uintptr_t)cur + SML_PG_OFSET && (uintptr_t)ptr <= (uintptr_t)cur + PAGESIZE && ((uintptr_t)ptr - (uintptr_t)cur) %				SML_ALLOC_SIZE >= TS_ALHEADR_SIZ)
			return ((void *)((uintptr_t)ptr - ((SML_ALLOC_SIZE % (uintptr_t)ptr) - TS_ALHEADR_SIZ)));
		cur = cur->next_page;
	}
	return (0);
}

static void		*check_large(void *ptr)
{
	struct s_lAllocHeader	*cur;

	cur = info->lallocs;
	while (cur)
	{
		if ((uintptr_t)ptr >= (uintptr_t)cur + LRG_ALHEADR_SIZ && (uintptr_t)ptr <= (uintptr_t)cur + cur->size)
			return ((void *)((uintptr_t)ptr - ((cur->size % (uintptr_t)ptr) - LRG_ALHEADR_SIZ)));
		cur = cur->next_alloc;
	}
	return (0);
}

unsigned int	find_header(void *ptr, void *header)
{
	header = 0;
	header = check_tiny(ptr);
	if (header)
		return (TINY);
	header = check_small(ptr);
	if (header)
		return (SMALL);
	header = check_large(ptr);
	if (header)
		return (LARGE);
	return (0);
}
