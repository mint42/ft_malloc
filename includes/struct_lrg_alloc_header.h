/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_lrg_alloc_header.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 16:18:06 by rreedy            #+#    #+#             */
/*   Updated: 2020/03/04 16:18:57 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_LRG_ALLOC_HEADER_H
# define STRUCT_LRG_ALLOC_HEADER_H

# include <stddef.h>

/*
**	This struct is stored at the front of the allocated memory
**	(All large allocations are 1+ pages.)
*/

struct							s_lrg_alloc_header
{
	size_t						used;
	size_t						size;
	struct s_lrg_alloc_header	*prev_alloc;
	struct s_lrg_alloc_header	*next_alloc;
};

#endif
