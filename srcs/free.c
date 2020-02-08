/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:52:38 by rreedy            #+#    #+#             */
/*   Updated: 2020/02/06 17:54:41 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "struct_tsPageHeader.h"
#include "struct_tsAllocHeader.h"
#include "struct_lAllocHeader.h"
#include <sys/mman.h>

static void		free_tiny(struct s_tsAllocHeader *header)
{
	struct s_tsPageHeader	*page_header;

	page_header = (struct s_tsPageHeader *)(header - (g_malloc->pagesize & (size_t)header));
	if (page_header->nallocs == 1 && g_malloc->ntpages > NPAGES_OVERHEAD)
		munmap(page_header, g_malloc->pagesize);
	else
	{
		--page_header->nallocs;
		g_malloc->free_tallocs_tail->next_free = header;
		g_malloc->free_tallocs_tail = g_malloc->free_tallocs_tail->next_free;
	}
}

//	for if unmapping needs to happen -> else if ()

static void		free_small(struct s_tsAllocHeader *header)
{
	struct s_tsPageHeader	*page_header;

	page_header = (struct s_tsPageHeader *)(header - (g_malloc->pagesize & (size_t)header));
	if (page_header->nallocs == 1 && g_malloc->nspages > NPAGES_OVERHEAD)
		munmap(page_header, g_malloc->pagesize);
	else
	{
		--page_header->nallocs;
		g_malloc->free_sallocs_tail->next_free = header;
		g_malloc->free_sallocs_tail = g_malloc->free_sallocs_tail->next_free;
	}
}

static void		free_large(struct s_lAllocHeader *header)
{
	struct s_lAllocHeader	*prev;

	prev = header->prev_alloc;
	if (!prev)
		g_malloc->lallocs = g_malloc->lallocs->next_alloc;
	else
		prev->next_alloc = header->next_alloc;
	munmap(header, header->size);
}

void			free(void *ptr)
{
	void			*header;
	unsigned int	zone;

	header = 0;
	zone = find_header(ptr, header);
	if (zone == TINY)
		free_tiny(header);
	else if (zone == SMALL)
		free_small(header);
	else if (zone == LARGE)
		free_large(header);
}
