#ifndef STRUCT_TSPAGEHEADER_H
# define STRUCT_TSPAGEHEADER_H

# include <stddef.h>

# define N_TINY_ALLOCS_PER_PAGE
# define N_SMALL_ALLOCS_PER_PAGE 

/*
**	Linked list of allocated pages.
**	Used at the very front of tiny and small pages to link them together.
*/

struct					s_tsPageHeader
{
	size_t				start_addr;
	unsigned short		nused;
	s_tsPageHeader		*next_page;
};

void				init_tsAllocHeader(s_tsPageHeader *header);

#endif
