/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_local.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 00:34:07 by rreedy            #+#    #+#             */
/*   Updated: 2020/02/02 00:39:00 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_LOCAL_H
# define STRUCT_LOCAL_H

# include <stddef.h>

/*
**	2 Linked lists of allocated nodes.
**	(small-medium allocs and large allocs)
*/

/*
**	For small/med allocs, the next pointer will only be needed if the space is
**	free. If so, it will be added to a linked list of other free nodes. For
**	quick access.
*/

struct				s_smalloc
{
	size_t			used;
	s_local			*next_free;
};

/*
**	For large allocs, it will be used as a pointer to the next large alloc.
**	All of which are 1+ pages.
*/

struct				s_lalloc
{
	size_t			used;
	size_t			size;
	s_local			*next_alloc;
};

/*
**	Linked list of allocated PAGES.
**	Used at the head of small and medium allocated pages.
*/

struct				s_page
{
	size_t			start_addr;
	size_t			end_addr;
	size_t			nfree;
	s_local			*next_page;
};

#endif
