/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_global.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 00:33:56 by rreedy            #+#    #+#             */
/*   Updated: 2020/03/04 20:12:52 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_STRUCT_S_MALLOC_H
# define GLOBAL_STRUCT_S_MALLOC_H

# include "struct_tnysml_mmap_header.h"
# include "struct_tnysml_alloc_header.h"
# include "struct_lrg_alloc_header.h"
# include <unistd.h>

/*
**	Global struct holding heads and tails to the different zones, and also
**	a "stack" of free-for-use allocations
*/

struct								s_malloc
{
	struct s_tnysml_mmap_header		*tny_mmaps;
	struct s_tnysml_mmap_header		*tny_mmaps_tail;
	struct s_tnysml_mmap_header		*sml_mmaps;
	struct s_tnysml_mmap_header		*sml_mmaps_tail;
	struct s_tnysml_alloc_header	*free_tny_allocs;
	struct s_tnysml_alloc_header	*free_tny_allocs_tail;
	struct s_tnysml_alloc_header	*free_sml_allocs;
	struct s_tnysml_alloc_header	*free_sml_allocs_tail;
	struct s_lrg_alloc_header		*lrg_allocs;
	size_t							pagesize;
	size_t							lrg_alheadr_siz;
	size_t							tnysml_alheadr_siz;
	size_t							tnysml_mpheadr_siz;
	size_t							n_tny_mmaps;
	size_t							n_sml_mmaps;
	size_t							tny_mmap_size;
	size_t							sml_mmap_size;
	size_t							tny_mmap_pad;
	size_t							sml_mmap_pad;
	size_t							tny_mmap_offset;
	size_t							sml_mmap_offset;
	size_t							tny_mmap_space;
	size_t							sml_mmap_space;
	size_t							n_tny_allocs_per_mmap;
	size_t							n_sml_allocs_per_mmap;
};

void								setup_malloc(void);

#endif
