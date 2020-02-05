#ifndef STRUCT_LALLOCHEADER_H
# define STRUCT_LALLOCHEADER_H

/*
**	For large allocs, it will be used as a pointer to the next large alloc.
**	This struct is stored at the front of the allocated memory
**	(All large allocations are 1+ pages.)
*/

# include <stddef.h>

struct				s_lAllocHeader
{
	size_t			used;
	size_t			size;
	size_t			start_addr;
	s_local			*next_alloc;
};

void				*init_lAllocHeader(size_t used_size);

#endif
