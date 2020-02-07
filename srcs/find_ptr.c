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

static void		*check_tiny(void *ptr)
{
	struct s_tsPageHeader	*cur;
	unsigned int			i;

	cur = g_malloc->tallocs;
	i = 0;
	while (i < N_TNY_ALOCS_PER_PG)
	{
		if (ptr >= cur->start_addr && ptr <= cur->start_addr + TNY_PG_SPACE)
			return (cur[ptr - (TNY_ALOC_SIZ % ptr) - TS_ALOC_HEADR_SIZ]);
		++i;
		cur = cur->next;

	}
	return (0);
}

static void		*check_small(void *ptr)
{
	struct s_tsPageHeader	*cur;
	unsigned int			i;

	cur = malloc_info->sallocs;
	i = 0;
	while (i < N_SML_ALOCS_PER_PG)
	{
		if (ptr >= cur->start_addr && ptr <= cur->start_addr + SML_PG_SPACE)
			return (cur[ptr - (SML_ALOC_SIZ % ptr) - TS_ALOC_HEADR_SIZ]);
		++i;
		cur = cur->next;

	}
	return (0);
}

static void		*check_large(void *ptr)
{
	struct s_lAllocHeader	*cur;

	cur = malloc_info->lallocs;
	while (cur)
	{
		if (ptr >= cur->start_addr && ptr <= cur->start_addr + cur->size)
			return (cur[ptr - (cur->size % ptr) - LRG_ALOC_HEADR_SIZ]);
		cur = cur->next;
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
		return (LARGE)
	return (0)
}
