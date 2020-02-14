/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:52:38 by rreedy            #+#    #+#             */
/*   Updated: 2020/02/14 06:50:47 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "struct_tsPageHeader.h"
#include "struct_tsAllocHeader.h"
#include "struct_lAllocHeader.h"
#include <sys/mman.h>
#include <unistd.h>

static void		free_tiny(void *header)
{
	struct s_tsPageHeader	*page_header;

	page_header = (struct s_tsPageHeader *)((uintptr_t)header - ((uintptr_t)header % info->pagesize));
	if (page_header->nallocs == 1 && info->ntpages > NPAGES_OVERHEAD)
		munmap(page_header, info->pagesize);
	else
	{
		--page_header->nallocs;
		info->free_tallocs_tail->next_free = header;
		info->free_tallocs_tail = info->free_tallocs_tail->next_free;
	}
}

static void		free_small(void *header)
{
	struct s_tsPageHeader	*page_header;

	page_header = (struct s_tsPageHeader *)((uintptr_t)header - ((uintptr_t)header % info->pagesize));
	if (page_header->nallocs == 1 && info->nspages > NPAGES_OVERHEAD)
		munmap(page_header, info->pagesize);
	else
	{
		--page_header->nallocs;
		info->free_sallocs_tail->next_free = header;
		info->free_sallocs_tail = info->free_sallocs_tail->next_free;
	}
}

static void		free_large(void *header)
{
	struct s_lAllocHeader	*prev;

	prev = ((struct s_lAllocHeader *)(header))->prev_alloc;
	if (!prev)
		info->lallocs = info->lallocs->next_alloc;
	else
		prev->next_alloc = ((struct s_lAllocHeader *)(header))->next_alloc;
	munmap(header, ((struct s_lAllocHeader *)(header))->size);
}

void			free(void *ptr)
{
	void			*header;
	unsigned int	zone;

	if (!info)
		setup_malloc();
	header = 0;
	zone = find_header(ptr, &header);
	if (zone == TINY)
		free_tiny(header);
	else if (zone == SMALL)
		free_small(header);
	else if (zone == LARGE)
		free_large(header);
}
