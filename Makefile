# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agouet <agouet@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/20 16:34:58 by agouet            #+#    #+#              #
#    Updated: 2022/07/13 15:02:09 by agouet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	minishell
LIBFT		= 	libft/libft.a
SRCS		=	$(addprefix sources/, \
					builtins/builtins_bis.c \
					builtins/builtins.c \
					builtins/environment_bis.c \
					builtins/environment.c \
					minishell_split/minishell_split_bis.c \
					minishell_split/minishell_split.c \
					operator/heredoc.c \
					operator/minishell_pipe.c \
					operator/operator_bonus.c \
					operator/operator.c \
					execut.c \
					ft_env_pipe.c \
					ft_env.c \
					initialisation.c \
					list_token.c \
					ft_is_str.c \
					ft_quoting.c \
					parsing.c \
					minishell.c \
					main.c \
					debug.c \
					monitor.c \
					parsing2.c \
				)
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
	$(MAKE) fclean -C libft
	rm -f $(NAME)

re: fclean
	make

.PHONY:	all re clean fclean

-include $(DEPS)
