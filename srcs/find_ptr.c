/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ptr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:22:23 by rreedy            #+#    #+#             */
/*   Updated: 2020/02/06 17:54:41 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "struct_tsPageHeader.h"
#include "struct_tsAllocHeader.h"
#include "struct_lAllocHeader.h"
#include <stddef.h>

static void		*check_tiny(void *ptr)
{
	struct s_tsPageHeader	*cur;

	cur = g_malloc->tpages;
	while (cur)
	{
		if (ptr >= cur->start_addr && ptr <= cur->start_addr + TNY_PG_SPACE)
			return (cur->start_addr + ((size_t)ptr - (TNY_ALOC_SIZ % (size_t)ptr) - TS_ALOC_HEADR_SIZ));
		cur = cur->next_page;
	}
	return (0);
}

static void		*check_small(void *ptr)
{
	struct s_tsPageHeader	*cur;

	cur = g_malloc->spages;
	while (cur)
	{
		if (ptr >= cur->start_addr && ptr <= cur->start_addr + SML_PG_SPACE)
			return (cur->start_addr + ((size_t)ptr - (SML_ALOC_SIZ % (size_t)ptr) - TS_ALOC_HEADR_SIZ));
		cur = cur->next_page;
	}
	return (0);
}

static void		*check_large(void *ptr)
{
	struct s_lAllocHeader	*cur;

	cur = g_malloc->lallocs;
	while (cur)
	{
		if (ptr >= cur->start_addr && ptr <= cur->start_addr + cur->size)
			return (cur->start_addr + ((size_t)ptr - (cur->size % (size_t)ptr) - LRG_ALOC_HEADR_SIZ));
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
