#include "malloc.h"
#include "ft_printf.h"
#include <stddef.h>
#include <stdlib.h>

static void		free_tiny(struct s_tsAllocHeader *header)
{
	malloc_info->free_tallocs_tail->next = header;
	malloc_info->free_tallocs_tail = malloc_info->free_tallocs_tail->next;
}

static void		free_small(struct s_tsAllocHeader *header)
{
	malloc_info->free_tallocs_tail->next = header;
	malloc_info->free_tallocs_tail = malloc_info->free_tallocs_tail->next;
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
