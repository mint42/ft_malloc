/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 00:36:23 by rreedy            #+#    #+#             */
/*   Updated: 2020/02/13 21:32:58 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "struct_tsPageHeader.h"
#include "struct_tsAllocHeader.h"
#include "struct_lAllocHeader.h"
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

// tests:
// run leaks to see if need to unmap pages -> wont work
// run free first to see if segfault and need to init malloc from any of them
//

int		main()
{
	char	*str;

	str = malloc(5);
	strcpy(str, "test");
	printf("%s\n", str);
	realloc(str, 9);
	strcpy(str, "new test");
	printf("%s\n", str);
	realloc(str, 20);
	strcpy(str, "new test with new :)");
	printf("%s\n", str);
	str = realloc(str, 1000);
	strcpy(str, "v65QWQ6qBFJzWIvAxB3s8sOfROWWmunixDCrkX56x4gvAm9G0DqeMJewRC9A3gJbwyMqSt7Ip0k4AfMwrFRtFgUqbH0boYHRqD3rQ3CCJDHINadB6Y0MxC4q0M8zj4RlQeivx5tQiTraRKgsq85aB4UABPFWjnHCkPw1CDFzcnfjxgBAn4n1Fpwp9YHKY0t0MN2vgTGCQUHowChJSI92PtDy6tNA0qNcETTtji2OoSc2ZmGpC7aPDxTH52QaLeGDxbLfiFz9UXxeIbs5Km14tVURxP50ILN7fZl8DaG7wVJLFkOZtHFoD32GrQAoupjAufKLnXeLeutVc71n50nKUWdRDjLpTlvnYNOocTQqfODmdKpS4Tb9sBAheMPbGTwA7w9mRM3aguUNgORks2OqFW2d5n4fvmSkKzmZepfSmLCccJUA6J4b0LAX6grFzpLJdKLdf2Jt8wrqEu8UFzf17obEogLuhn8J5bGFVd2w414RIfdNJh4NuurIfbR8CYDj4cbMocV8dqAmK6MPA4cWXiBbHdgqPYtBWfmbtdwjO9mvGwlkQ6L25QxTq1ZCIPf23vX96fyBGdsY1nfNbGvTjSHQWeBxZJgPaZlPtDiKiKn6pKqweRzESQ20LLbExvGwoALviArZSJ24vRMzMWoyAvpyfIliVK7p89v99Fc8t4nRu77x9tSpBMWWiH7DKFfvzsfYiMdgNnNBSI5P5lxOnr8KW1HHd4Y2BTwy4P6VL0n3zDiBEVRpVj5kgxHriAev6z7tkIZilBtykh07l5LYXDTq90jkAMLxfCtIlqv8YNm8Y6zF71ybSkOoFuZSV4Cn8KvSTbGb9lcuSEJQ2j0xlcoS7s70Pfwp4EHqx7pgl8Xy8WUkl0C4RrbuOlI8rh2Yo83s51VKbycTJDQ3XC4Es4rsG97msthRoUROWq8VysLSXk7eWiNMcWZOpz5A9XRfsMKdBEfY1c6ssprEQl6ygJjq5hwzM1Zlf2bR2B1");
	printf("%s\n", str);
	return (0);
}
