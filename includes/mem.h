/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 18:48:11 by rreedy            #+#    #+#             */
/*   Updated: 2020/02/08 18:48:24 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_H
# define MEM_H


void	zero_mem(void *ptr, int a, size_t size);
void	cpy_mem(void *new_ptr, void *ptr, size_t size);

#endif
