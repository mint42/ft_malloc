/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_tsAllocHeader.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:07:17 by rreedy            #+#    #+#             */
/*   Updated: 2020/02/19 16:59:43 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_TSALLOCHEADER_H
# define STRUCT_TSALLOCHEADER_H

/*
**	For tiny/small allocs, the next pointer will only be needed if the space is
**	free. And if so, it will be added to a linked list of other free nodes for
**	quick access.
*/
struct							s_tsAllocHeader
{
	unsigned short				free;
	unsigned short				used;
	struct s_tsAllocHeader		*next_free;
};

#endif
