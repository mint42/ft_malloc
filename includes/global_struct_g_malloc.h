/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_global.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 00:33:56 by rreedy            #+#    #+#             */
/*   Updated: 2020/02/14 00:22:08 by rreedy           ###   ########.fr       */
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
	struct s_tsPageHeader	*tpages;
	struct s_tsPageHeader	*tpages_tail;
	struct s_tsPageHeader	*spages;
	struct s_tsPageHeader	*spages_tail;
	struct s_tsAllocHeader	*free_tallocs;
	struct s_tsAllocHeader	*free_tallocs_tail;
	struct s_tsAllocHeader	*free_sallocs;
	struct s_tsAllocHeader	*free_sallocs_tail;
	struct s_lAllocHeader	*lallocs;
	size_t					ntpages;
	size_t					nspages;
	size_t					pagesize;
	size_t					lrg_alheadr_siz;
	size_t					ts_alheadr_siz;
	size_t					ts_pgheadr_siz;
	size_t					tny_pg_pad;
	size_t					sml_pg_pad;
	size_t					tny_pg_offset;
	size_t					sml_pg_offset;
	size_t					tny_pg_space;
	size_t					sml_pg_space;
	size_t					n_tny_alocs_per_pg;
	size_t					n_sml_alocs_per_pg;
};

#endif
