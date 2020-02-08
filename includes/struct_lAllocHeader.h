/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_lAllocHeader.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:20:08 by rreedy            #+#    #+#             */
/*   Updated: 2020/02/06 17:21:59 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_LALLOCHEADER_H
# define STRUCT_LALLOCHEADER_H

# include <stddef.h>

# define LRG_ALOC_HEADR_SIZ 40

/*
**	This struct is stored at the front of the allocated memory
**	(All large allocations are 1+ pages.)
*/

struct						s_lAllocHeader
{
	void					*start_addr;
	size_t					used;
	size_t					size;
	struct s_lAllocHeader	*prev_alloc;
	struct s_lAllocHeader	*next_alloc;
};

#endif
