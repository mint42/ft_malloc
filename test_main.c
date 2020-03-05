/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 00:36:23 by rreedy            #+#    #+#             */
/*   Updated: 2020/03/04 16:48:28 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "struct_tnysml_mmap_header.h"
#include "struct_tnysml_alloc_header.h"
#include "struct_lrg_alloc_header.h"
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

int		main()
{
	char	*str;

	str = malloc(12);
	strcpy(str, "tiny malloc");
	printf("%p: %s\n", str, str);
	str = realloc(str, 14);
	strcpy(str, "tiny malloc 2");
	printf("%p: %s\n", str, str);
	str = realloc(str, 29);
	strcpy(str, "small malloc 1. is it small?");
	printf("%p: %s\n", str, str);
	str = realloc(str, 35);
	strcpy(str, "small malloc 2. is it STILL small?");
	printf("%p: %s\n", str, str);
	str = realloc(str, 14);
	strcpy(str, "tiny malloc 3");
	printf("%p: %s\n", str, str);
	str = realloc(str, 1000);
	strcpy(str, "v65QWQ6qBFJzWIvAxB3s8sOfROWWmunixDCrkX56x4gvAm9G0DqeMJewRC9A3gJbwyMqSt7Ip0k4AfMwrFRtFgUqbH0boYHRqD3rQ3CCJDHINadB6Y0MxC4q0M8zj4RlQeivx5tQiTraRKgsq85aB4UABPFWjnHCkPw1CDFzcnfjxgBAn4n1Fpwp9YHKY0t0MN2vgTGCQUHowChJSI92PtDy6tNA0qNcETTtji2OoSc2ZmGpC7aPDxTH52QaLeGDxbLfiFz9UXxeIbs5Km14tVURxP50ILN7fZl8DaG7wVJLFkOZtHFoD32GrQAoupjAufKLnXeLeutVc71n50nKUWdRDjLpTlvnYNOocTQqfODmdKpS4Tb9sBAheMPbGTwA7w9mRM3aguUNgORks2OqFW2d5n4fvmSkKzmZepfSmLCccJUA6J4b0LAX6grFzpLJdKLdf2Jt8wrqEu8UFzf17obEogLuhn8J5bGFVd2w414RIfdNJh4NuurIfbR8CYDj4cbMocV8dqAmK6MPA4cWXiBbHdgqPYtBWfmbtdwjO9mvGwlkQ6L25QxTq1ZCIPf23vX96fyBGdsY1nfNbGvTjSHQWeBxZJgPaZlPtDiKiKn6pKqweRzESQ20LLbExvGwoALviArZSJ24vRMzMWoyAvpyfIliVK7p89v99Fc8t4nRu77x9tSpBMWWiH7DKFfvzsfYiMdgNnNBSI5P5lxOnr8KW1HHd4Y2BTwy4P6VL0n3zDiBEVRpVj5kgxHriAev6z7tkIZilBtykh07l5LYXDTq90jkAMLxfCtIlqv8YNm8Y6zF71ybSkOoFuZSV4Cn8KvSTbGb9lcuSEJQ2j0xlcoS7s70Pfwp4EHqx7pgl8Xy8WUkl0C4RrbuOlI8rh2Yo83s51VKbycTJDQ3XC4Es4rsG97msthRoUROWq8VysLSXk7eWiNMcWZOpz5A9XRfsMKdBEfY1c6ssprEQl6ygJjq5hwzM1Zlf2bR2B1");
	printf("%p: %s\n", str, str);

	char	**allocs;

	allocs = (char **)malloc(sizeof(char *) * 500);
	for (int i = 0; i < 500; i++)
	{
		printf("TINY TEST #%d\n", i + 1);
		allocs[i] = malloc(16);
		memset(allocs[i], (i + 1) % 26 + 97, 15);
		allocs[i][15] = '\0';
		printf("%p: %s\n", allocs[i], allocs[i]);
	}
	for (int i = 0; i < 20; i++)
	{
		printf("SMALL TEST #%d\n", i + 1);
		allocs[i] = realloc(allocs[i], 500);
		memset(allocs[i], (i + 1) % 26 + 97, 499);
		allocs[i][499] = '\0';
		printf("%p: %s\n", allocs[i], allocs[i]);
	}
	for (int i = 0; i < 5; i++)
	{
		printf("LARGE TEST #%d\n", i + 1);
		allocs[i] = realloc(allocs[i], 1000);
		memset(allocs[i], (i + 1) % 26 + 97, 999);
		allocs[i][999] = '\0';
		printf("%p: %s\n", allocs[i], allocs[i]);
	}
	for (int i = 0; i < 500; i++)
	{
		free(allocs[i]);
	}
	free(allocs + 100);

	char	*a = malloc(16);
	a[0] = 'a';
	a = realloc(a + 1, 32);
	printf("[%s]\n", a);
	free(a + 1);
	a = realloc(a + 1, 64);
	if (a)
		printf("err\n");

	return (0);
}
