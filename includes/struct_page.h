#ifndef STRUCT_PAGE_H
# define STRUCT_PAGE_H

/*
**	Linked list of allocated PAGES.
**	Used at the head of small and medium allocated pages.
*/

struct				s_page
{
	size_t			start_addr;
	size_t			nfree;
	s_local			*next_page;
};

#endif
