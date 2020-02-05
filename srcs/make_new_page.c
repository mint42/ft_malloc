#include "struct_tsPageHeader.h"
#include "struct_tsAllocHeader.h"
#include <stddef.h>

static void		fill_page(void *new_page, unsigned int alloc_size)
{
	struct s_tsPageHeader	*new_aheader;
	void					*cur;
	size_t					i;

	i = (alloc_size == TINY_ALLOC_SIZE) ? N_TINY_ALLOCS : N_SMALL_ALLOCS;
	new_aheader = (s_tsAllocHeader)cur;
	init_tsAllocHeader(new_aheader);
	cur = cur + alloc_size;
	--i;
	while (i > 0)
	{
		new_aheader->next_free = cur;
		new_aheader = (s_tsAllocHeader)cur;
		init_tsAllocHeader(new_aheader);
		cur = cur + alloc_size;
		--i;
	}
}

void			*make_tspage(unsigned int alloc_size)
{
	void					*new_page;
	struct s_tsPageHeader	*new_pheader;

	new_page = mmap(getpagesize());
	if (!new_page)
		return (ERROR);
	new_pheader = (s_tsPageHeader)new_page;
	init_tsPageHeader(new_pheader);
	new_pheader->start_addr = new_page +
			sizeof(struct s_tsAllocHeader) + sizeof(struct s_tsPageHeader);
	fill_page(new_page);
	return (new_page);
}
