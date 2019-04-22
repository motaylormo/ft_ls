# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/12 16:25:14 by mtaylor           #+#    #+#              #
#    Updated: 2019/04/12 16:25:15 by mtaylor          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
FLAGS = -Wall -Wextra -Werror

LIB = -I libft/ ./libft/libft.a

SRC = main.c \
	  read.c \
	  sort.c \
	  print_longform.c print_longform_annex.c \
	  print_shortform.c \
	  queue.c \
	  util.c


all: $(NAME)

$(NAME): $(OFILES)
	make -s -C ./libft
	gcc $(FLAGS) $(LIB) $(addprefix ./src/, $(SRC)) -o $(NAME)

debug:
	make -s -C ./libft
	gcc $(FLAGS) -g $(LIB) $(addprefix ./src/, $(SRC)) -o $(NAME)

fsan:
	make -s -C ./libft
	gcc $(FLAGS) -fsanitize=address $(LIB) $(addprefix ./src/, $(SRC)) -o $(NAME)

clean:
	make -s -C ./libft clean

fclean: clean
	make -s -C ./libft fclean
	rm -f $(NAME)
	rm -f -R $(addsuffix .dSYM, $(NAME))

re: fclean all