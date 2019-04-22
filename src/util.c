/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 16:20:36 by mtaylor           #+#    #+#             */
/*   Updated: 2019/04/14 16:20:37 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	*print_error(char *str, char *error_str, char *full_path)
{
	PRINT_ERROR(str, error_str);
	if (full_path)
		free(full_path);
	return (NULL);
}

char	*cat_pathname(char *path, char *addition)
{
	char	*new;

	if (path == NULL)
		return (ft_strdup(addition));
	new = ft_strnew(ft_strlen(path) + ft_strlen(addition) + 1);
	new = ft_strcpy(new, path);
	if (new[ft_strlen(new) - 1] != '/')
		new[ft_strlen(new)] = '/';
	new = ft_strcat(new, addition);
	return (new);
}

void	free_node(t_node *n)
{
	if (n->name)
		free(n->name);
	if (n->path)
		free(n->path);
	if (n->pw_name)
		free(n->pw_name);
	if (n->gr_name)
		free(n->gr_name);
	free(n);
}

void	free_queue(t_queue *q)
{
	while (q->first)
		free_node(dequeue(q));
	if (q->name)
		free(q->name);
	if (q->path)
		free(q->path);
	free(q);
}
