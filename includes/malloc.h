#ifndef FT_MALLOC_H
# define FT_MALLOC_H

#include "global_struct_g_malloc.h"
#include <stddef.h>

# define TINY 1
# define SMALL 2
# define LARGE 3

# define NPAGES_OVERHEAD 5

struct g_malloc	*g_malloc;

void			*malloc(size_t size);
void			*realloc(void *ptr, size_t size);
void			free(void *ptr);

/*
**	Manage Malloc
*/

void			setup_malloc(void);
void			add_ts_page(unsigned int zone);
void			add_large_alloc(size_t used_size);
unsigned int	find_header(void *ptr, void *header);

#endif
