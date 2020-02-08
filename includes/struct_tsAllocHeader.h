/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_tsAllocHeader.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:07:17 by rreedy            #+#    #+#             */
/*   Updated: 2020/02/06 17:33:55 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_TSALLOCHEADER_H
# define STRUCT_TSALLOCHEADER_H

/*
**	READ COMMENTS BEFORE ADJUSTING!
*/

/*
**	sizeof(s_tsPageHeader)
**	sizeof(s_tsAllocHeader)
*/
# define TS_PG_HEADR_SIZ 18
# define TS_ALOC_HEADR_SIZ 10

/*
** Padding after page header for better alignment of allocations
*/
# define TNY_PG_PAD 4
# define SML_PG_PAD 4

/*
**	Allocation size and allocations-per-page is a based on these numbers.
**	It calculate the remaining page space which can be divided into individual
**	allocations (either tiny or small).
**	
**	             (4096 bytes)
**	*_PG_SPACE = getpagesize() - (TS_PG_HEADR_SIZE + *_PG_HEADR_PAD)
*/
# define TNY_PG_SPACE 4074
# define SML_PG_SPACE 4074

/*
**	After choosing a suitable padding for the front of a page, and have figured
**	out *_PG_SPACE. You can factor that number to find values for
**	*_N_ALLOCS_PER_PG and *_ALLOC_SIZ
*/
# define N_TNY_ALOCS_PER_PG 97
# define N_SML_ALOCS_PER_PG 14

/*
**	This equation yields the actual space available for one allocation:
**
**	*_ALOC_SIZ = (*_PG_SPACE / N_TNY_ALOCS_PER_PG) - TS_ALOC_HEADR_SIZ
*/
# define TNY_ALOC_SIZ 32
# define SML_ALOC_SIZ 281

/*
**	For tiny/small allocs, the next pointer will only be needed if the space is
**	free. And if so, it will be added to a linked list of other free nodes for
**	quick access.
*/

struct							s_tsAllocHeader
{
	unsigned short				used;
	struct s_tsAllocHeader		*next_free;
};

#endif
