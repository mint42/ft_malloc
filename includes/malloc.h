#ifndef FT_MALLOC_H
# define FT_MALLOC_H

#include <stddef.h>

void	*ft_malloc(size_t size);
void	*ft_realloc(void *ptr, size_t size);
void	ft_free(void *ptr);

void	*make_large_alloc(size_t used_size);
void	*make_ts_page(unsigned int zone);
void	setup_malloc(void);

#endif
