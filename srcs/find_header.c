/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ptr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:22:23 by rreedy            #+#    #+#             */
/*   Updated: 2020/02/22 04:38:12 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "struct_tsPageHeader.h"
#include "struct_tsAllocHeader.h"
#include "struct_lAllocHeader.h"
#include <stddef.h>
#include <unistd.h>

#include <stdio.h>
static void		*check_tiny(void *ptr)
{
	struct s_tsPageHeader	*cur;
	struct s_tsAllocHeader	*header;

	cur = info->tpages;
	while (cur)
	{
		if ((uintptr_t)ptr >= (uintptr_t)cur + info->tny_pg_offset && (uintptr_t)ptr < (uintptr_t)cur + info->pagesize && ((uintptr_t)ptr - ((uintptr_t)cur + info->tny_pg_offset)) % (info->ts_alheadr_siz + TNY_ALLOC_SIZE) >= info->ts_alheadr_siz)
		{
			header = (struct s_tsAllocHeader *)((uintptr_t)cur + info->tny_pg_offset + ((info->ts_alheadr_siz + TNY_ALLOC_SIZE) *
			(((uintptr_t)ptr - ((uintptr_t)cur + info->tny_pg_offset)) / (info->ts_alheadr_siz + TNY_ALLOC_SIZE))));
			return ((!header->free) ? header : 0);
		}
		cur = cur->next_page;
	}
	return (0);
}

static void		*check_small(void *ptr)
{
	struct s_tsPageHeader	*cur;
	struct s_tsAllocHeader	*header;

	cur = info->spages;
	while (cur)
	{
		if ((uintptr_t)ptr >= (uintptr_t)cur + info->sml_pg_offset && (uintptr_t)ptr < (uintptr_t)cur + info->pagesize && ((uintptr_t)ptr - ((uintptr_t)cur + info->sml_pg_offset)) % (info->ts_alheadr_siz + SML_ALLOC_SIZE) >= info->ts_alheadr_siz)
		{
			header = (struct s_tsAllocHeader *)((uintptr_t)cur + info->sml_pg_offset + ((info->ts_alheadr_siz + SML_ALLOC_SIZE) *
			(((uintptr_t)ptr - ((uintptr_t)cur + info->sml_pg_offset)) / (info->ts_alheadr_siz + SML_ALLOC_SIZE))));
			return ((!header->free) ? header : 0);
		}
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
		if ((uintptr_t)ptr >= (uintptr_t)cur + info->lrg_alheadr_siz && (uintptr_t)ptr <= (uintptr_t)cur + cur->size)
			return (cur);
		cur = cur->next_alloc;
	}
	return (0);
}

unsigned int	find_header(void *ptr, void **header)
{
	*header = 0;
	*header = check_tiny(ptr);
	if (*header)
		return (TINY);
	*header = check_small(ptr);
	if (*header)
		return (SMALL);
	*header = check_large(ptr);
	if (*header)
		return (LARGE);
	return (0);
}
