/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 11:32:23 by mtaylor           #+#    #+#             */
/*   Updated: 2019/04/14 11:32:25 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	quicksort_queue(t_queue *q, int (*f)(t_node*, t_node*))
{
	t_queue	*subq1;
	t_queue	*subq2;
	t_node	*pivot;
	t_node	*n;

	if (!q || q->len < 2)
		return ;
	subq1 = init_queue();
	subq2 = init_queue();
	pivot = dequeue(q);
	while ((n = dequeue(q)))
	{
		enqueue(
			((*f)(pivot, n)) ? subq1 : subq2,
			n);
	}
	enqueue(subq1, pivot);
	quicksort_queue(subq1, (*f));
	quicksort_queue(subq2, (*f));
	while (subq1->first)
		enqueue(q, dequeue(subq1));
	while (subq2->first)
		enqueue(q, dequeue(subq2));
	free_queue(subq1);
	free_queue(subq2);
}

/*
**	Sort by time modified (most recently modified first)
*/

static int	t_sort(t_node *node, t_node *pivot)
{
	if (node->date < pivot->date)
		return (1);
	if (node->date == pivot->date)
	{
		if (node->time < pivot->time)
			return (1);
	}
	return (0);
}

/*
**	Sort by ascii value of filename
*/

static int	ascii_sort(t_node *node, t_node *pivot)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(node->name) && i < ft_strlen(pivot->name))
	{
		if (node->name[i] < pivot->name[i])
			return (0);
		if (node->name[i] > pivot->name[i])
			return (1);
		if (node->name[i] == pivot->name[i])
			i++;
	}
	if (i == ft_strlen(node->name))
		return (0);
	else
		return (1);
}

/*
**	Reverse the queue
*/

static void	reverse_queue(t_queue *q)
{
	t_node	*node;

	if (!q || !q->first)
		return ;
	else
	{
		node = dequeue(q);
		reverse_queue(q);
		enqueue(q, node);
	}
}

void		sort_queue(t_queue *q, int flags)
{
	if (flags & flag_t)
		quicksort_queue(q, t_sort);
	else
		quicksort_queue(q, ascii_sort);
	if (flags & flag_r)
		reverse_queue(q);
}
