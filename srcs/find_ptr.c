static void		*check_tiny(void *ptr)
{
	struct s_tsPageHeader	*cur;
	unsigned int			i;

	cur = malloc_info->tallocs;
	i = 0;
	while (i < N_TINY_ALLOCS_PER_PAGE)
	{
		if (ptr >= cur->start_addr && ptr <= cur->start_addr + malloc_info->page_size)
			return (cur[ptr - (TINY_ALLOC_SIZE % ptr) - sizeof(struct tsAllocHeader)]);
		++i;
		cur = cur->next;

	}
	return (0);
}

static void		*check_small(void *ptr)
{
	struct s_tsPageHeader	*cur;
	unsigned int			i;

	cur = malloc_info->sallocs;
	i = 0;
	while (i < N_SMALL_ALLOCS_PER_PAGE)
	{
		if (ptr >= cur->start_addr && ptr <= cur->start_addr + malloc_info->page_size)
			return (cur[ptr - (SMALL_ALLOC_SIZE % ptr) - sizeof(struct tsAllocHeader)]);
		++i;
		cur = cur->next;

	}
	return (0);
}

static void		*check_large(void *ptr)
{
	struct s_lAllocHeader	*cur;

	cur = malloc_info->lallocs;
	while (cur)
	{
		if (ptr >= cur->start_addr && ptr <= cur->start_addr + cur->size)
			return (cur[ptr - (cur->size % ptr) - sizeof(struct lAllocHeader)]);
		cur = cur->next;
	}
	return (0);
}

unsigned int	find_header(void *ptr, void *header)
{
	header = 0;
	header = check_tiny();
	if (header)
		return (TINY);
	header = check_small();
	if (header)
		return (SMALL);
	header = check_large();
	return (headeR)
}
