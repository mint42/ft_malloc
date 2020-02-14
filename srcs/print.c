#include "malloc.h"
#include "global_struct_g_malloc.h"
#include <stdio.h>

void	print(void)
{
	printf("info->ntpages               %zu\n", info->ntpages);
	printf("info->nspages               %zu\n", info->nspages);
	printf("info->pagesize              %zu\n", info->pagesize);
	printf("info->lrg_alheadr_siz       %zu\n", info->lrg_alheadr_siz);
	printf("info->ts_alheadr_siz        %zu\n", info->ts_alheadr_siz);
	printf("info->ts_pgheadr_siz        %zu\n", info->ts_pgheadr_siz);
	printf("info->tny_pg_pad            %zu\n", info->tny_pg_pad);
	printf("info->sml_pg_pad            %zu\n", info->sml_pg_pad);
	printf("info->tny_pg_offset         %zu\n", info->tny_pg_offset);
	printf("info->sml_pg_offset         %zu\n", info->sml_pg_offset);
	printf("info->tny_pg_space          %zu\n", info->tny_pg_space);
	printf("info->sml_pg_space          %zu\n", info->sml_pg_space);
	printf("info->n_tny_alocs_per_pg    %zu\n", info->n_tny_alocs_per_pg);
	printf("info->n_sml_alocs_per_pg    %zu\n", info->n_sml_alocs_per_pg);
}
