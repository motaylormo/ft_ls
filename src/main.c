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

static int	parse_flags(int ac, char **av)
{
	int	c;
	int	flags;

	flags = 0;
	while ((c = ft_getopt(ac, av, "atrRl@f")) != -1)
	{
		if (c == '?')
			exit(1);
		if (c == 'a')
			flags |= flag_a;
		if (c == 't')
			flags |= flag_t;
		if (c == 'r')
			flags |= flag_r;
		if (c == 'R')
			flags |= flag_R;
		if (c == 'l')
			flags |= flag_l;
		if (c == '@')
			flags |= flag_xattr;
	}
	return (flags);
}

void		sort_and_print_queue(char *dir_name, char *prev_path, int flags)
{
	t_queue		*q;

	if (!(q = dir_to_queue(dir_name, prev_path, flags)))
		return ;
	sort_queue(q, flags);
	(flags & flag_l) ? long_form_print(q, flags) : short_form_print(q);
	if (flags & flag_R)
		recusion(q, flags);
	free_queue(q);
}

void		recusion(t_queue *q, int flags)
{
	t_node	*n;

	while ((n = dequeue(q)))
	{
		if (S_ISDIR(n->mode) &&
			!ft_strequ(n->name, ".") && !ft_strequ(n->name, ".."))
		{
			ft_printf("\n%s/%s:\n", q->path, n->name);
			sort_and_print_queue(n->name, q->path, flags);
		}
		free_node(n);
	}
}

static void	multi_args(int ac, char **av, int i, int flags)
{
	t_queue	*q;
	t_node	*n;

	q = init_queue();
	while (i < ac)
	{
		if ((n = node_from_stat(av[i], NULL, flags)))
			enqueue(q, n);
		i++;
	}
	sort_queue(q, flags);
	while (q->first)
	{
		n = dequeue(q);
		ft_printf("%s:\n", n->name);
		sort_and_print_queue(n->name, NULL, flags);
		if (q->first)
			ft_printf("\n");
		free_node(n);
	}
	free_queue(q);
}

int			main(int ac, char **av)
{
	int		flags;

	flags = parse_flags(ac, av);
	if (optind < ac)
	{
		if (optind == ac - 1)
			sort_and_print_queue(av[optind], NULL, flags);
		else
			multi_args(ac, av, optind, flags);
	}
	else
		sort_and_print_queue(".", NULL, flags);
}
