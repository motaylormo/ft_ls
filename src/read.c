/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 18:28:51 by mtaylor           #+#    #+#             */
/*   Updated: 2019/04/12 18:28:52 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	struct passwd {
**		char	*pw_name;	- username
**		char	*pw_passwd;	- user password encrypted
**		uid_t	pw_uid;		- user ID
**		gid_t	pw_gid;		- group ID
**		time_t	pw_change;	- password change time
**		char	*pw_class;	- user access class
**		char	*pw_gecos;	- user's full name
**		char	*pw_dir;	- user's login directory
**		char	*pw_shell;	- user's login shell
**		time_t	pw_expire;	- password expiration time
**	};
**	struct group {
**		char	*gr_name;	- group name
**		char	*gr_passwd;	- encrypted password
**		gid_t	gr_gid;		- group ID
**		char	**gr_mem;	- list of group members
**	};
*/

static void	flag_specific_info(t_node *n, struct stat statbuf, int flags)
{
	struct passwd	*pwd;
	struct group	*grp;

	n->date = statbuf.st_mtimespec.tv_sec;
	n->time = statbuf.st_mtimespec.tv_nsec;
	if (flags & flag_l)
	{
		pwd = getpwuid(statbuf.st_uid);
		n->pw_name = (pwd) ? ft_strdup(pwd->pw_name) : ft_itoa(statbuf.st_uid);
		grp = getgrgid(statbuf.st_gid);
		n->gr_name = (grp) ? ft_strdup(grp->gr_name) : ft_itoa(statbuf.st_gid);
	}
}

t_node		*node_from_stat(char *file_name, char *prev_path, int flags)
{
	t_node			*n;
	struct stat		statbuf;
	int				ret;
	char			*full_path;

	full_path = cat_pathname(prev_path, file_name);
	ret = (flags & flag_l) ? lstat(full_path, &statbuf) :
							stat(full_path, &statbuf);
	if (ret == 0)
		n = ft_memalloc(sizeof(t_node));
	else
		return (print_error(file_name, strerror(errno), full_path));
	n->name = ft_strdup(file_name);
	n->path = full_path;
	n->mode = statbuf.st_mode;
	n->nlink = statbuf.st_nlink;
	n->byte_size = statbuf.st_size;
	n->blocks = statbuf.st_blocks;
	n->rdev = statbuf.st_rdev;
	if ((flags & flag_t) || (flags & flag_l))
		flag_specific_info(n, statbuf, flags);
	return (n);
}

t_queue		*dir_to_queue(char *dir_name, char *prev_path, int flags)
{
	DIR				*dir;
	struct dirent	*dp;
	t_queue			*q;
	t_node			*n;
	char			*full_path;

	full_path = cat_pathname(prev_path, dir_name);
	if (!(dir = opendir(full_path)))
		return (print_error(dir_name, strerror(errno), full_path));
	q = init_queue();
	q->name = ft_strdup(dir_name);
	q->path = full_path;
	while ((dp = readdir(dir)) != NULL)
	{
		if (dp->d_name[0] != '.' || (flags & flag_a))
		{
			if ((n = node_from_stat(dp->d_name, q->path, flags)))
				enqueue(q, n);
		}
	}
	closedir(dir);
	return (q);
}
