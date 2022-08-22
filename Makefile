# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agouet <agouet@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/20 16:34:58 by agouet            #+#    #+#              #
#    Updated: 2022/08/22 10:36:52 by agouet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	minishell
LIBFT		= 	libft/libft.a
SRCS		=	$(addprefix sources/, \
					builtins/builtins_bis.c \
					builtins/builtins.c \
					builtins/environment_bis.c \
					builtins/environment.c \
					minishell_split/ft_env_pipe.c \
					minishell_split/ft_env_quote.c \
					minishell_split/ft_env.c \
					minishell_split/minishell_split_bis.c \
					minishell_split/minishell_split.c \
					operator/heredoc.c \
					operator/heredoc2.c \
					operator/minishell_pipe.c \
					operator/minishell_pipe2.c \
					operator/operator_bonus.c \
					operator/operator.c \
					parsing/ft_quoting.c \
					parsing/list_token.c \
					parsing/parsing.c \
					parsing/parsing2.c \
					useful/ft_getenv.c \
					useful/ft_is_int.c \
					useful/ft_is_str.c \
					useful/useful.c \
					useful/free.c \
					execut_bis.c \
					execut.c \
					initialisation.c \
					minishell.c \
					main.c \
					monitor.c \
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

vtest:				$(NAME)
					valgrind --leak-check=full --track-fds=yes\
					--show-leak-kinds=all\
					--suppressions=.ignore_readline ./$(NAME)

.PHONY:	all re clean fclean

-include $(DEPS)
