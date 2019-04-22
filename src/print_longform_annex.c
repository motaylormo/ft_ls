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

#define LINK_BUF_SIZE 256

/*
**	11 chars:
**	1	file type
**			'-'	regular file
**			'd'	directory
**			'c'	character special file (a device like a terminal)
**			'b'	block special file (a device like a disk)
**			'l'	symbolic link
**			'p'	FIFO special file, or a pipe
**			's'	socket
**	3	owner permissions (read, write, execute)
**	3	group permissions (read, write, execute)
**	3	everyone else permissions (read, write, execute)
**	1	extended stuff
**			'@'	has extended attributes
**			'+'	has extended security information (ACL, access control list)
**			' '	neither extended attributes nor ACL
*/

static char	parse_file_type(mode_t mode)
{
	if (S_ISREG(mode))
		return ('-');
	if (S_ISDIR(mode))
		return ('d');
	if (S_ISLNK(mode))
		return ('l');
	if (S_ISBLK(mode))
		return ('b');
	if (S_ISCHR(mode))
		return ('c');
	if (S_ISSOCK(mode))
		return ('s');
	if (S_ISFIFO(mode))
		return ('p');
	return (' ');
}

void		print_file_mode(t_node *n)
{
	char	c[11];
	acl_t	acl_suf;

	ft_memset(c, ' ', 11);
	c[0] = parse_file_type(n->mode);
	c[1] = (S_IRUSR & n->mode) ? 'r' : '-';
	c[2] = (S_IWUSR & n->mode) ? 'w' : '-';
	c[3] = (S_IXUSR & n->mode) ? 'x' : '-';
	c[4] = (S_IRGRP & n->mode) ? 'r' : '-';
	c[5] = (S_IWGRP & n->mode) ? 'w' : '-';
	c[6] = (S_IXGRP & n->mode) ? 'x' : '-';
	c[7] = (S_IROTH & n->mode) ? 'r' : '-';
	c[8] = (S_IWOTH & n->mode) ? 'w' : '-';
	c[9] = (S_IXOTH & n->mode) ? 'x' : '-';
	if ((listxattr(n->path, NULL, XATTR_MAXNAMELEN, XATTR_NOFOLLOW) > 0))
		c[10] = '@';
	else if ((acl_suf = acl_get_link_np(n->path, ACL_TYPE_EXTENDED)))
	{
		acl_free(acl_suf);
		c[10] = '+';
	}
	ft_printf("%.11s ", c);
}

void		if_link(t_node *n)
{
	char	link_str[LINK_BUF_SIZE];
	int		ret;

	ret = readlink(n->path, link_str, LINK_BUF_SIZE);
	ft_printf(" -> %.*s", ret, link_str);
}

void		if_extended_attributes(t_node *n)
{
	char	buf[XATTR_MAXNAMELEN];
	int		size;
	int		ret;
	int		i;

	if ((ret = listxattr(n->path, buf, XATTR_MAXNAMELEN, XATTR_NOFOLLOW)))
	{
		i = 0;
		while (i < ret)
		{
			size = getxattr(n->path, buf + i, NULL,
							XATTR_MAXNAMELEN, 0, XATTR_NOFOLLOW);
			ft_printf("\t%s\t\t%d\n", buf + i, size);
			i += ft_strlen(buf + i) + 1;
		}
	}
}

void		print_time(t_node *n)
{
	char	*ptr;
	time_t	now;

	ptr = ctime(&(n->date));
	now = time(NULL);
	if (n->date <= (now - SIX_MONTHS))
		ft_printf("%.6s %5.4s ", ptr + 4, ptr + 20);
	else
		ft_printf("%.12s ", ptr + 4);
}
