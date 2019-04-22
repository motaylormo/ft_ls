/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 11:00:27 by mtaylor           #+#    #+#             */
/*   Updated: 2019/04/12 11:00:29 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

/*
**		FOR ALLOWED FUNCTIONS
**	<dirent.h>		for opendir() & readdir() & closedir()
**	<sys/stat.h>	for stat() & lstat()
**	<sys/xattr.h>	for listxattr() & getxattr()
**	<time.h>		for time() & ctime()
**	<sys/types.h>	for macros major() & minor()
**	<uuid/uuid.h> <grp.h> <sys/types.h>	for getgrgid()
**	<uuid/uuid.h> <pwd.h>				for getpwuid()
**	<string.h> <errno.h>	for strerror()
**	<unistd.h>	for readlink()
**	<stdlib.h>	for exit()
**
** 		FOR "management of ACL and extended attributes" BONUS
**	<sys/types.h> <sys/acl.h>
*/
# include "../libft/libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <uuid/uuid.h>
# include <sys/types.h>
# include <grp.h>
# include <pwd.h>
# include <sys/xattr.h>
# include <time.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <stdlib.h>
# include <sys/acl.h>

typedef struct s_node	t_node;
struct	s_node{
	t_node		*next;
	char		*path;
	char		*name;
	mode_t		mode;
	nlink_t		nlink;
	dev_t		rdev;
	off_t		byte_size;
	quad_t		blocks;
	time_t		date;
	long		time;
	char		*pw_name;
	char		*gr_name;
};

typedef struct s_queue	t_queue;
struct	s_queue{
	int		len;
	char	*path;
	char	*name;
	t_node	*first;
	t_node	*last;
};

/*
**	-a	Include directory entries whose names begin with a dot (.)
**	-t	Sort by time modified (most recently modified first).
**	-r	After other sorts, reverse the order.
**	-R	Recursively list subdirectories encountered.
**	-l	List in long form.
**	-@	Display extended attribute keys and sizes in long (-l) output.
*/
enum	e_flags{
	flag_a = 1 << 0,
	flag_R = 1 << 1,
	flag_r = 1 << 2,
	flag_t = 1 << 3,
	flag_l = 1 << 4,
	flag_xattr = 1 << 5,
};

# define PRINT_ERROR(file, error) ft_printf("./ft_ls: %s: %s\n", file, error)
# define SIX_MONTHS	((time_t)(60 * 60 * 24 * (365 / 2)))

/*
**	main.c
*/
void	sort_and_print_queue(char *dir_name, char *dir_path, int flags);
void	recusion(t_queue *q, int flags);

/*
**	read.c
*/
t_queue	*dir_to_queue(char *dir_name, char *dir_path, int flags);
t_node	*node_from_stat(char *d_name, char *path, int flags);

/*
**	sort.c
*/
void	sort_queue(t_queue *q, int flags);

/*
**	prints
*/
void	print_file_mode(t_node *n);
void	print_time(t_node *n);
void	if_link(t_node *n);
void	if_extended_attributes(t_node *n);

void	long_form_print(t_queue *q, int flags);
void	short_form_print(t_queue *q);

/*
**	queue.c
*/
t_queue	*init_queue(void);
void	enqueue(t_queue *q, t_node *n);
t_node	*dequeue(t_queue *q);

/*
**	util.c
*/
void	*print_error(char *str, char *error_str, char *full_path);
char	*cat_pathname(char *path, char *addition);
void	free_node(t_node *n);
void	free_queue(t_queue *q);

#endif
