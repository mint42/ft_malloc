#ifndef STRUCT_LALLOCHEADER_H
# define STRUCT_LALLOCHEADER_H

/*
**	This struct is stored at the front of the allocated memory
**	(All large allocations are 1+ pages.)
*/

# include <stddef.h>

struct				s_lAllocHeader
{
	size_t			used;
	size_t			size;
	size_t			start_addr;
	s_lAllocHeader	*prev_alloc;
	s_lAllocHeader	*next_alloc;
};

#endif
