#include "malloc.h"
#include "global_struct_s_malloc.h"
#include <stdio.h>

void	print(void)
{
	printf("info->lrg_alheadr_siz         %zu\n", info->lrg_alheadr_siz);
	printf("info->ts_alheadr_siz          %zu\n", info->tnysml_alheadr_siz);
	printf("info->ts_pgheadr_siz          %zu\n", info->tnysml_mpheadr_siz);
	printf("info->ntmmaps                 %zu\n", info->n_tny_mmaps);
	printf("info->nsmmaps                 %zu\n", info->n_sml_mmaps);
	printf("info->tny_mmap_size           %zu\n", info->tny_mmap_size);
	printf("info->sml_mmap_size           %zu\n", info->sml_mmap_size);
	printf("info->tny_mmap_pad            %zu\n", info->tny_mmap_pad);
	printf("info->sml_mmap_pad            %zu\n", info->sml_mmap_pad);
	printf("info->tny_mmap_offset         %zu\n", info->tny_mmap_offset);
	printf("info->sml_mmap_offset         %zu\n", info->sml_mmap_offset);
	printf("info->tny_mmap_space          %zu\n", info->tny_mmap_space);
	printf("info->sml_mmap_space          %zu\n", info->sml_mmap_space);
	printf("info->n_tny_alocs_per_mmap    %zu\n", info->n_tny_allocs_per_mmap);
	printf("info->n_sml_alocs_per_mmap    %zu\n", info->n_sml_allocs_per_mmap);
}
