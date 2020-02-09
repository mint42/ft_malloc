/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_tsPageHeader.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:07:46 by rreedy            #+#    #+#             */
/*   Updated: 2020/02/08 20:14:54 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_TSPAGEHEADER_H
# define STRUCT_TSPAGEHEADER_H

# include <stddef.h>

# define TS_PGHEADR_SIZ (sizeof(struct s_tsPageHeader))

/*
**	Linked list of allocated pages.
**	Stored at the very front of tiny and small pages to link them together.
*/
struct						s_tsPageHeader
{
	void					*start_addr;
	unsigned short			nallocs;
	struct s_tsPageHeader	*next_page;
};

#endif
