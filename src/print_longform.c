/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 11:00:12 by mtaylor           #+#    #+#             */
/*   Updated: 2019/04/12 11:00:15 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	The following information is displayed for each file:
**		1. file mode
**		2. number of links
**		3. owner name
**		4. group name,
**		5. number of bytes in the file
**		6. [month | day-of-month | hour:minute] file last modified
**		7. file name
**
**	In addition, for each directory whose contents are displayed, the total
**	number of 512-byte blocks used by the files in the directory is displayed
**	on a line by itself, immediately before the information for the files in
**	the directory.
*/

#define DEV_NUM(mode)			(S_ISBLK(mode) || S_ISCHR(mode))
#define UPDATE_MAX(curr, max)	if (curr > max) max = curr

static void	outline(t_queue *q, int field_width[4])
{
	size_t	blocks;
	t_node	*n;

	n = q->first;
	blocks = 0;
	bzero(field_width, sizeof(int) * 4);
	while (n)
	{
		UPDATE_MAX((ft_intmaxlen(n->nlink, 10)), field_width[0]);
		UPDATE_MAX((int)(ft_strlen(n->pw_name)), field_width[1]);
		UPDATE_MAX((int)(ft_strlen(n->gr_name)), field_width[2]);
		UPDATE_MAX(
			(DEV_NUM(n->mode)) ? 8 : ft_intmaxlen(n->byte_size, 10),
			field_width[3]);
		blocks += n->blocks;
		n = n->next;
	}
	if (q->first)
		ft_printf("total %zu\n", blocks);
}

void		long_form_print(t_queue *q, int flags)
{
	t_node	*n;
	int		field_width[4];

	n = q->first;
	outline(q, field_width);
	while (n)
	{
		print_file_mode(n);
		ft_printf("%*d ", field_width[0], n->nlink);
		ft_printf("%-*s ", field_width[1] + 1, n->pw_name);
		ft_printf("%-*s ", field_width[2] + 1, n->gr_name);
		(DEV_NUM(n->mode)) ?
			ft_printf("%3d, %3d ", major(n->rdev), minor(n->rdev)) :
			ft_printf("%*lld ", field_width[3], n->byte_size);
		print_time(n);
		ft_printf("%s", n->name);
		if (S_ISLNK(n->mode))
			if_link(n);
		ft_printf("\n");
		if (flags & flag_xattr)
			if_extended_attributes(n);
		n = n->next;
	}
}
