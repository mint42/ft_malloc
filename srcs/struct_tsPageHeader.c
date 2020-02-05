# include "struct_tsPageHeader.h"

void				init_tsPageHeader(struct s_tsPageHeader *header)
{
	header.start_addr = 0;
	header.nfree = 0;
	header.next_page = 0;
}
