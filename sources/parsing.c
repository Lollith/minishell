/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 10:08:20 by agouet            #+#    #+#             */
/*   Updated: 2022/07/11 11:54:52 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_quote(char *line)
{
	int	i;
	int	two;
	int	one;

	if (!line)
		return (FALSE);
	two = 0;
	one = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\"')
			two++;
		if (line[i] == '\'')
			one++;
		i++;
	}
	if (two % 2 == 1 || one % 2 == 1)
		return (FALSE);
	return (TRUE);
}

// fonction qui cree les "mots" en fonction des espaces
// token est free dans minishell par ft_free_split
char	**lexer(char *line)
{
	char	**token;

	if (!ft_quote(line))
		return (NULL);
	token = minishell_split(line, " \t\n\v\f\r");
	if (!token)
		return (NULL);
	return (token);
}

// cherche les flag et les files dune commande,
//les met ds args_ecxec pour la commande exec,
// et les sort de la liste chainee
int	size_args(t_list *l_token)
{
	int			size;
	t_list		*tmp_token;
	struct stat	info;

	size = 2;
	tmp_token = l_token;
	while ((tmp_token->next && (ft_strchr(tmp_token->next->content, '-')
				|| (stat(tmp_token->next->content, &info) == 0))))
	{
		size++;
		tmp_token = tmp_token->next;
	}
	return (size);
}

char	**ft_is_arg(t_list *l_token)
{
	char		**args_exec;
	int			size;
	int			i;

	args_exec = NULL;
	size = size_args(l_token);
	args_exec = (char **)malloc(sizeof(char *) * size);
	if (!args_exec)
		return (FAILURE);
	args_exec[0] = (l_token)->content;
	i = 1;
	while (l_token && i < size - 1)
	{
		args_exec[i] = (l_token)->next->content;
		i++;
		ft_l_delete(l_token);
	}
	args_exec[size - 1] = NULL;
	return (args_exec);
}

//si cmd < file1 => <file cmd => passe ds ft_isarg => tab de [0]"<" [1]"file" => < cat
// logiuement la cmd va se retourvee systematiquenet a ka fin  cat < file1 < file2 => < file1 < file2 < cat
void	reorganize(t_list **l_token)
{
	if (((*l_token)->next && ft_strncmp((*l_token)->next->content, "<", 1) == 0)
	|| ((*l_token)->next && ft_strncmp((*l_token)->next->content, ">", 1) == 0))
	{
		t_list		*tmp;

		tmp = (*l_token)->next;
		if ((*l_token)->next->next->next)
			(*l_token)->next = (*l_token)->next->next->next;
		else
			(*l_token)->next = NULL;

		(tmp->next->next) = (*l_token);
		(*l_token) = tmp;
	}
}
