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
# include <stdbool.h>

struct				s_local
{
	bool			free;
	size_t			used;
	size_t			size;
	size_t			npages;
	size_t			pagen;
	s_local			*next_page;
	s_local			*next;
};

#endif
