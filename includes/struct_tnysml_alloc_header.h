/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_tnysml_alloc_header.h                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 16:19:57 by rreedy            #+#    #+#             */
/*   Updated: 2020/03/04 16:21:15 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_TNYSML_ALLOC_HEADER_H
# define STRUCT_TNYSML_ALLOC_HEADER_H

/*
**	For tiny/small allocations, the next pointer will only be needed if the
**	space is free. And if so, it will be added to a linked list of other free
**	nodes for quick mallocing.
*/

struct								s_tnysml_alloc_header
{
	unsigned char					free;
	unsigned short					used;
	unsigned short					id;
	struct s_tnysml_alloc_header	*next_free;
};

#endif
