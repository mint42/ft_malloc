/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 00:36:23 by rreedy            #+#    #+#             */
/*   Updated: 2020/02/09 04:36:14 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "struct_tsPageHeader.h"
#include "struct_tsAllocHeader.h"
#include "struct_lAllocHeader.h"
#include <string.h>
#include <stddef.h>
#include <stdio.h>

// tests:
// run leaks to see if need to unmap pages
// run free first to see if segfault and need to init malloc from any of them
//

int		main()
{
	char	*str;

	str = malloc(5);
	strcpy(str, "test");
	printf("%s\n", (char  *)str);
	realloc(str, 9);
	strcpy(str, "new test");
	printf("%s\n", (char  *)str);
	free(str);
	return (0);
}
