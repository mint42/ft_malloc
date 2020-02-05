#ifndef STRUCT_TSALLOC_H
# define STRUCT_TSALLOC_H

# define SIZE_TALLOC
# define SIZE_SALLOC

/*
**	For tiny/small allocs, the next pointer will only be needed if the space is
**	free. If so, it will be added to a linked list of other free nodes. For
**	quick access.
*/

struct				s_tsalloc
{
	size_t			used;
	s_local			*next_free;
};

#endif
