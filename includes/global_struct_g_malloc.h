/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_global.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 00:33:56 by rreedy            #+#    #+#             */
/*   Updated: 2020/02/02 00:34:02 by rreedy           ###   ########.fr       */
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

struct					g_malloc
{
	s_tsPageHeader		*tpages;
	s_tsPageHeader		*tpages_tail;
	s_tsPageHeader		*spages;
	s_tsPageHeader		*spages_tail;
	s_lAllocHeader		*lallocs;
	s_lAllocHeader		*lallocs_tail;
	s_tsAllocHeader		*free_tallocs;
	s_tsAllocHeader		*free_sallocs;
	size_t				ntpages;
	size_t				nspages;
};

#endif
