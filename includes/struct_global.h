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
	s_page			*small_pages;
	s_page			*medium_pages;
	s_lalloc		*large_allocs;
	s_smalloc		*small_free;
	s_smalloc		*medium_free;
	size_t			n_spages;
	size_t			n_mpages;
	size_t			n_lallocs;
};

#endif
