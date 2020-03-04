/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_global.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 00:33:56 by rreedy            #+#    #+#             */
/*   Updated: 2020/03/02 20:53:59 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_STRUCT_G_MALLOC_H
# define GLOBAL_STRUCT_G_MALLOC_H

#include "struct_tsPageHeader.h"
#include "struct_tsAllocHeader.h"
#include "struct_lAllocHeader.h"
#include <stddef.h>

/*
**	Global struct holding heads and tails to the different zones, and also
**	a "stack" of free-for-use spaces
*/

struct						g_malloc
{
	struct s_tsPageHeader	*tmmaps;
	struct s_tsPageHeader	*tmmaps_tail;
	struct s_tsPageHeader	*smmaps;
	struct s_tsPageHeader	*smmaps_tail;
	struct s_tsAllocHeader	*free_tallocs;
	struct s_tsAllocHeader	*free_tallocs_tail;
	struct s_tsAllocHeader	*free_sallocs;
	struct s_tsAllocHeader	*free_sallocs_tail;
	struct s_lAllocHeader	*lallocs;
	size_t					pagesize;
	size_t					lrg_alheadr_siz;
	size_t					ts_alheadr_siz;
	size_t					ts_pgheadr_siz;
	size_t					ntmmaps;
	size_t					nsmmaps;
	size_t					tny_mmap_size;
	size_t					sml_mmap_size;
	size_t					tny_mmap_pad;
	size_t					sml_mmap_pad;
	size_t					tny_mmap_offset;
	size_t					sml_mmap_offset;
	size_t					tny_mmap_space;
	size_t					sml_mmap_space;
	size_t					n_tny_alocs_per_mmap;
	size_t					n_sml_alocs_per_mmap;
};

void						setup_malloc(void);

#endif
