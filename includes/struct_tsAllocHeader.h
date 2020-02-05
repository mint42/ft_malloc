#ifndef STRUCT_TSALLOCHEADER_H
# define STRUCT_TSALLOCHEADER_H

/*
**	For tiny/small allocs, the next pointer will only be needed if the space is
**	free. If so, it will be added to a linked list of other free nodes. For
**	quick access.
*/

# include <stddef.h>

struct				s_tsAllocHeader
{
	size_t			used;
	s_local			*next_free;
};

void				init_tsAllocHeader(s_tsAllocHeader *header);

#endif
