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

#ifndef STRUCT_GLOBAL_H
# define STRUCT_GLOBAL_H

#include "struct_local.h"

struct				s_global
{
	s_page			*tpages;
	s_page			*tpages_tail;
	s_page			*spages;
	s_page			*spages_tail;
	s_lalloc		*lallocs;
	s_lalloc		*lallocs_tail;
	s_tsalloc		*tallocs_free;
	s_tsalloc		*sallocs_free;
	size_t			ntpages;
	size_t			nspages;
};

#endif
