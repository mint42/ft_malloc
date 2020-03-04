/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_tsPageHeader.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:07:46 by rreedy            #+#    #+#             */
/*   Updated: 2020/03/02 20:56:33 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_TSPAGEHEADER_H
# define STRUCT_TSPAGEHEADER_H

# include <stddef.h>

/*
**	Linked list of allocated pages.
**	Stored at the very front of tiny and small pages to link them together.
*/
struct						s_tsPageHeader
{
	unsigned short			nallocs;
	struct s_tsPageHeader	*next_mmap;
};

#endif
