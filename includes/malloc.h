#ifndef FT_MALLOC_H
# define FT_MALLOC_H

#include "global_struct_g_malloc.h"
#include <stddef.h>

# define TINY 1
# define SMALL 2
# define LARGE 3

# define NPAGES_OVERHEAD 5

struct g_malloc		*malloc_info;

void	*ft_malloc(size_t size);
void	*ft_realloc(void *ptr, size_t size);
void	ft_free(void *ptr);

void	*make_large_alloc(size_t used_size);
void	*make_ts_page(unsigned int zone);
void	setup_malloc(void);

#endif
