/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_global.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 00:33:56 by rreedy            #+#    #+#             */
/*   Updated: 2020/02/02 00:34:02 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_GLOBAL_H
# define STRUCT_GLOBAL_H

#include "struct_local.h"

struct				s_global
{
	s_local			*small;
	s_local			*medium;
	s_local			*large;
	unsigned int	nsmall;
	unsigned int	nsmallfree;
	unsigned int	nmedium;
	unsigned int	nmediumfree;
	unsigned int	nlarge;
	unsigned int	nlargefree;
};

#endif
