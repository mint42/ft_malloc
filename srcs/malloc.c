#include "malloc.h"
#include "ft_printf.h"
#include <stddef.h>
#include <stdlib.h>

void		*make_large_alloc(size_t used_size)
{
	struct s_lAllocHeader	*new_header;
	void					*new_alloc;
	size_t					page_size;

	page_size = getpagesize();
	new_header->used = used_size;
	new_header->size = (used_size / page_size) + page_size;
	new_alloc = mmap(new_header.size);
	if (!new_alloc)
		return (ERROR);
	new_header->start_addr = new_alloc + sizeof(s_lAllocHeader);
	ft_memcpy(new_alloc, new_header);
	new_header->prev_alloc = malloc_info.lAlloc_tail->next_alloc;
	new_header->next_alloc = 0;
	return (new_alloc);
}

static void		fill_tiny_page(void *new_page)
{
	struct s_tsPageHeader	*new_aheader;
	void					*cur;
	unsigned int			i;

	new_aheader = (s_tsAllocHeader)cur;
	new_aheader->used = 0;
	new_aheader->next = 0;
	cur = cur + TINY_ALLOC_SIZE;
	i = N_TINY_ALLOCS_ON_PAGE - 1;
	while (i > 0)
	{
		new_aheader->next_free = cur;
		new_aheader = (s_tsAllocHeader)cur;
		new_aheader->used = 0;
		new_aheader->next = 0;
		malloc_info->free_tallocs_tail->next = new_aheader;
		malloc_info->free_tallocs_tail = malloc_info->free_tallocs_tail->next;
		cur = cur + TINY_ALLOC_SIZE;
		--i;
	}
	malloc_info->tpages_tail->next = new_page;
	malloc_info->tpages_tail = malloc_info->tpages_tail->next;
	++malloc_info->tpages;
}

static void		fill_small_page(void *new_page)
{
	struct s_tsPageHeader	*new_aheader;
	void					*cur;
	unsigned int			i;

	new_aheader = (s_tsAllocHeader)cur;
	new_aheader->used = 0;
	new_aheader->next = 0;
	cur = cur + SMALL_ALLOC_SIZE;
	i = N_SMALL_ALLOCS_ON_PAGE - 1;
	while (i > 0)
	{
		new_aheader->next_free = cur;
		new_aheader = (s_tsAllocHeader)cur;
		new_aheader->used = 0;
		new_aheader->next = 0;
		malloc_info->free_sallocs_tail->next = new_aheader;
		malloc_info->free_sallocs_tail = malloc_info->free_sallocs_tail->next;
		cur = cur + SMALL_ALLOC_SIZE;
		--i;
	}
	malloc_info->spages_tail->next = new_page;
	malloc_info->spages_tail = malloc_info->spages_tail->next;
	++malloc_info->spages;
}

static void		*make_ts_page(unsigned int zone)
{
	void					*new_page;
	struct s_tsPageHeader	*new_pheader;

	new_page = mmap(getpagesize());
	if (!new_page)
		return (ERROR);
	new_pheader = (s_tsPageHeader)new_page;
	new_pheader->nfree = 0;
	new_pheader->next_page = 0;
	new_pheader->start_addr = new_page +
			sizeof(struct s_tsAllocHeader) + sizeof(struct s_tsPageHeader);
	if (zone == TINY)
		fill_tiny_page(new_page);
	else
		fill_small_page(new_page);
	return (new_page);
}

void			*ft_malloc(size_t size)
{
	void	*ptr;

	if (size <= TINY_ALLOC_SIZE)
	{
		if (!malloc_info.free_talloc)
			make_ts_page(TINY);
		ptr = malloc_info->free_talloc;
		malloc_info->free_talloc = malloc_info->free_talloc_next;
		((struct s_tsAllocHeader)(ptr))->used = size;
	}
	else if (size <= SMALL_ALLOC_SIZE)
	{
		if (!malloc_info.free_salloc)
			make_ts_page(SMALL);
		ptr = malloc_info->free_salloc;
		malloc_info->free_salloc = malloc_info->free_salloc_next;
		((struct s_tsAllocHeader)(ptr))->used = size;
	}
	else
		ptr = make_large_alloc(size);
	return (ptr);
}
