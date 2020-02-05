#ifndef STRUCT_TSPAGEHEADER_H
# define STRUCT_TSPAGEHEADER_H

/*
**	Linked list of allocated pages.
**	Used at the very front of tiny and small pages to link them together.
*/

# include <stddef.h>

struct					s_tsPageHeader
{
	size_t				start_addr;
	size_t				nfree;
	s_local				*next_page;
};

void				init_tsAllocHeader(s_tsPageHeader *header);

#endif
