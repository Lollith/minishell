/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 10:08:20 by agouet            #+#    #+#             */
/*   Updated: 2022/06/07 11:40:29 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// fonction qui cree les "mots" en fonction des espaces
// token est free dans minishell par ft_free_split
// a modifier => gerer les ; "" ''
// a modifier => gerer tous les espaces " \t\n\v\f\r"
// token = minishell_split(line, " \t\n\v\f\r");
char	**lexer(char *line)
{
	char	**token;

	token = ft_split(line, ' ');
	if (!token)
		return (NULL);
	return (token);
}

int	size_args(t_list *l_token)
{
	int			size;
	t_list		*tmp_token;
	struct stat	info;

	tmp_token = l_token;
	size = 2;
	while ((tmp_token->next && (ft_strchr(tmp_token->next->content, '-')
				|| (stat(tmp_token->next->content, &info) == 0))))
	{
		size++;
		tmp_token = tmp_token->next;
	}
	return (size);
}

char	**ft_is_arg(t_list *l_token) // too long
{
	char		**args_exec;
	int			size;
	int			i;

	size = size_args(l_token);
	args_exec = (char **)malloc(sizeof(char *) * size);
	if (!args_exec)
		return (FAILURE);
	args_exec[0] = l_token->content;
	i = 1;
	while (l_token && i < size - 1)
	{
		args_exec[i] = l_token->next->content;
		i++;
		ft_l_delete (l_token);
	}
	args_exec[size - 1] = NULL;
	return (args_exec);
}