/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_tnysml_mmap_header.h                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 16:21:35 by rreedy            #+#    #+#             */
/*   Updated: 2020/03/04 16:43:49 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_TNYSML_MMAP_HEADER_H
# define STRUCT_TNYSML_MMAP_HEADER_H

# include <stddef.h>

/*
**	Linked list of memory from mmap calls.
*/

struct								s_tnysml_mmap_header
{
	unsigned short					nallocs;
	struct s_tnysml_mmap_header		*next_mmap;
};

#endif
