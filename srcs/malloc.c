#include "malloc.h"
#include <stddef.h>
#include <stdlib.h>

void			*ft_malloc(size_t size)
{
	void	*ptr;

	if (!malloc_info)
		setup_malloc();
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
