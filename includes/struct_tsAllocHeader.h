#ifndef STRUCT_TSALLOCHEADER_H
# define STRUCT_TSALLOCHEADER_H


# include <stddef.h>

# define TINY_ALLOC_SIZE
# define SMALL_ALLOC_SIZE

/*
**	For tiny/small allocs, the next pointer will only be needed if the space is
**	free. If so, it will be added to a linked list of other free nodes. For
**	quick access.
*/

struct				s_tsAllocHeader
{
	unsigned short		used;
	s_tsAllocHeader		*next_free;
};

void				init_tsAllocHeader(s_tsAllocHeader *header);

#endif
