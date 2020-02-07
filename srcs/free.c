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

static void		free_tiny(struct s_tsAllocHeader *header)
{
	struct s_tsPageHeader	*page_header;

	page_header = header - (malloc_info->pagesize & (void *)header);
	if (page_header->nused == 1 && malloc_info->tpages > NPAGES_OVERHEAD)
		munmap(page_header);
	else
	{
		--page_header->nfree;
		malloc_info->free_tallocs_tail->next = header;
		malloc_info->free_tallocs_tail = malloc_info->free_tallocs_tail->next;
	}
}

//	for if unmapping needs to happen -> else if ()

static void		free_small(struct s_tsAllocHeader *header)
{
	struct s_tsPageHeader	*page_header;

	page_header = header - (malloc_info->pagesize & (void *)header);
	if (page_header->nused == 1 && malloc_info->spages > NPAGES_OVERHEAD)
		munmap(page_header);
	else
	{
		--page_header->nfree;
		malloc_info->free_sallocs_tail->next = header;
		malloc_info->free_sallocs_tail = malloc_info->free_sallocs_tail->next;
	}
}

static void		free_large(struct s_lAllocHeader *header)
{
	struct s_lAllocHeader	prev;

	prev = header->prev_alloc;
	if (!prev)
		malloc_info->lallocs = malloc_info->lallocs->next;
	else
		prev->next_alloc = header->next_alloc;
	munmap(header);
}

void			ft_free(void *ptr)
{
	void			*header;
	unsigned int	zone;

	zone = find_alloc(ptr, header);
	if (zone == TINY)
		free_tiny(header);
	else if (zone == SMALL)
		free_small(header);
	else if (zone == LARGE)
		free_large(header);
}
