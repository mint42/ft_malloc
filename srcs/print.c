#include "malloc.h"
#include "global_struct_g_malloc.h"
#include <stdio.h>

void	print(void)
{
	printf("info->lrg_alheadr_siz         %zu\n", info->lrg_alheadr_siz);
	printf("info->ts_alheadr_siz          %zu\n", info->ts_alheadr_siz);
	printf("info->ts_pgheadr_siz          %zu\n", info->ts_pgheadr_siz);
	printf("info->ntmmaps                 %zu\n", info->ntmmaps);
	printf("info->nsmmaps                 %zu\n", info->nsmmaps);
	printf("info->tny_mmap_size           %zu\n", info->tny_mmap_size);
	printf("info->sml_mmap_size           %zu\n", info->sml_mmap_size);
	printf("info->tny_mmap_pad            %zu\n", info->tny_mmap_pad);
	printf("info->sml_mmap_pad            %zu\n", info->sml_mmap_pad);
	printf("info->tny_mmap_offset         %zu\n", info->tny_mmap_offset);
	printf("info->sml_mmap_offset         %zu\n", info->sml_mmap_offset);
	printf("info->tny_mmap_space          %zu\n", info->tny_mmap_space);
	printf("info->sml_mmap_space          %zu\n", info->sml_mmap_space);
	printf("info->n_tny_alocs_per_mmap    %zu\n", info->n_tny_alocs_per_mmap);
	printf("info->n_sml_alocs_per_mmap    %zu\n", info->n_sml_alocs_per_mmap);
}

void	print2(void)
{
	struct s_tsAllocHeader	*tmp;

	tmp = info->free_tallocs;
	while (tmp)
	{
		printf("%p\n", tmp);
		tmp = tmp->next_free;
	}
}
