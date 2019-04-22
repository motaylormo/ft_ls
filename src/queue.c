/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 09:38:32 by exam              #+#    #+#             */
/*   Updated: 2019/03/26 10:13:01 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_queue	*init_queue(void)
{
	t_queue	*q;

	q = ft_memalloc(sizeof(t_queue));
	q->len = 0;
	q->name = NULL;
	q->first = NULL;
	q->last = NULL;
	return (q);
}

void	enqueue(t_queue *q, t_node *n)
{
	if (!n)
		return ;
	n->next = NULL;
	if (q->first == NULL)
		q->first = n;
	if (q->last == NULL)
		q->last = n;
	else
	{
		q->last->next = n;
		q->last = q->last->next;
	}
	q->len++;
}

t_node	*dequeue(t_queue *q)
{
	t_node	*n;

	if (!q || !q->first)
		return (NULL);
	n = q->first;
	if (n == q->last)
	{
		q->first = NULL;
		q->last = NULL;
	}
	else
		q->first = q->first->next;
	q->len--;
	return (n);
}
