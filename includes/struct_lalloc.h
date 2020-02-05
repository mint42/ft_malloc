#ifndef STRUCT_LALLOC_H
# define STRUCT_LALLOC_H
/*
**	For large allocs, it will be used as a pointer to the next large alloc.
**	All of which are 1+ pages.
*/

struct				s_lalloc
{
	size_t			used;
	size_t			size;
	s_local			*next_alloc;
};

#endif
