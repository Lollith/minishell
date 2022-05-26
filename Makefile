# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agouet <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/20 16:34:58 by agouet            #+#    #+#              #
#    Updated: 2022/04/20 16:47:22 by agouet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	minishell
LIBFT		= 	libft/libft.a
SRCS		=	$(addprefix sources/, execut.c ft_is_str.c minishell_split.c \
				parsing.c minishell.c main.c debug.c)
OBJS		=	$(SRCS:.c=.o)
DEPS		=	$(SRCS:.c=.d)
CC 			=	cc
CFLAGS		=	-Wall -Wextra -Werror -MMD -g3
READLINE	=	-lreadline 
INC			=	-I ./includes

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	$(MAKE) -C libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE) -o $(NAME)

all: $(NAME)

clean:
	$(MAKE) clean -C libft
	rm -f $(OBJS) $(DEPS)

fclean: clean
	${MAKE} fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY:	all re clean fclean

-include $(DEPS)
