# include "struct_tsAllocHeader.h"

void				init_tsAllocHeader(struct s_tsAllocHeader *header)
{
	header.used = 0;
	header.next_free = 0;
}
