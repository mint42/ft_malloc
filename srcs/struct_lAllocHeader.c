#include "global_struct_g_malloc.h" 
#include <stddef.h>

void		*make_large_alloc(size_t used_size)
{
	struct s_lAllocHeader	new_header;
	void					*new_alloc;
	size_t					page_size;

	page_size = getpagesize();
	new_header.used = used_size;
	new_header.size = (used_size / page_size) + page_size;
	new_alloc = mmap(new_header.size);
	if (!new_alloc)
		return (ERROR);
	new_header.start_addr = new_alloc + sizeof(s_lAllocHeader);
	ft_memcpy(new_alloc, new_header);
	malloc_info.lAlloc_tail->next_alloc = new_header;
	return (new_alloc);
}

#endif
