/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 03:03:10 by rreedy            #+#    #+#             */
/*   Updated: 2020/04/27 07:25:07 by mint             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "struct_tnysml_mmap_header.h"
#include "struct_tnysml_alloc_header.h"
#include "struct_lrg_alloc_header.h"
#include "ft_printf.h"
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

void	show_tny(void)
{
	struct s_tnysml_mmap_header		*cur;
	unsigned int					addr;
	unsigned int					used;
	size_t							i;

	cur = info->tny_mmaps;
	while (cur)
	{
		i = 0;
		while (i < info->n_tny_allocs_per_mmap)
		{
			addr = (uintptr_t)cur + info->tny_mmap_offset +
					((info->tnysml_alheadr_siz + TNY_ALLOC_SIZE) * i);
			used = ((struct s_tnysml_alloc_header *)
					((uintptr_t)cur + info->tny_mmap_offset +
					((info->tnysml_alheadr_siz + TNY_ALLOC_SIZE) * i)))->used;
			if (!(((struct s_tnysml_alloc_header *)
					((uintptr_t)cur + info->tny_mmap_offset +
					((info->tnysml_alheadr_siz + TNY_ALLOC_SIZE) * i)))->free))
			ft_printf("%#.8x - %#.8x : %d bytes\n", addr, addr + used, used);
			++i;
		}
		cur = cur->next_mmap;
	}
}

void	show_sml(void)
{
	struct s_tnysml_mmap_header		*cur;
	unsigned int					addr;
	unsigned int					used;
	size_t							i;

	cur = info->sml_mmaps;
	while (cur)
	{
		i = 0;
		while (i < info->n_sml_allocs_per_mmap)
		{
			addr = (uintptr_t)cur + info->sml_mmap_offset +
					((info->tnysml_alheadr_siz + SML_ALLOC_SIZE) * i);
			used = ((struct s_tnysml_alloc_header *)
					((uintptr_t)cur + info->sml_mmap_offset +
					((info->tnysml_alheadr_siz + SML_ALLOC_SIZE) * i)))->used;
			if (!(((struct s_tnysml_alloc_header *)
					((uintptr_t)cur + info->sml_mmap_offset +
					((info->tnysml_alheadr_siz + SML_ALLOC_SIZE) * i)))->free))
			ft_printf("%#.8x - %#.8x : %d bytes\n", addr, addr + used, used);
			++i;
		}
		cur = cur->next_mmap;
	}
}

void	show_lrg(void)
{
	struct s_lrg_alloc_header		*cur;
	unsigned int					addr;
	unsigned int					used;

	cur = info->lrg_allocs;
	while (cur)
	{
		addr = (uintptr_t)cur + info->lrg_alheadr_siz;
		used = cur->used;
		ft_printf("%#.8x - %#.8x : %d bytes\n", addr, addr + used, used);
		cur = cur->next_alloc;
	}
}

void	show_alloc_mem(void)
{
	write(1, "TINY :\n", 7);
	show_tny();
	write(1, "SMALL :\n", 8);
	show_sml();
	write(1, "LARGE :\n", 8);
	show_lrg();
}
