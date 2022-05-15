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

NAME 		= minishell

SRCS_PATH	= ./sources/

SRCS		= $(addprefix $(SRCS_PATH), main.c)

OBJS		= $(SRCS:.c=.o)

DEPS		= $(SRCS:.c=.d)

CC 			= cc

CFLAGS		= -MMD -Wall -Wextra -Werror -g 

READLINE	= -lreadline 

INC			= -I ./includes

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(READLINE)

%.o:		%.c
		$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean:		
		rm -f $(OBJS) $(DEPS)

fclean:		clean
		rm -f $(NAME)

re:			fclean all

.PHONY:		all re clean fclean

-include $(DEPS)
