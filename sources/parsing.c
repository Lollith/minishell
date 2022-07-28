/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 10:08:20 by agouet            #+#    #+#             */
/*   Updated: 2022/07/13 15:03:51 by agouet           ###   ########.fr       */
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
	char	*str;

	if (!ft_quote(line))
		return (NULL);
	str = ft_quoting(line);
	if (!str)
		return (NULL);
	token = minishell_split(str, MS_SPACE);	
	free(str);
	if (!token)
		return (NULL);
	return (token);
}

// si < ou > : next  paxsse ds mon tab execve
// sinon cherche si g un operateur 
// sinon met le toekn suivant ds args_ecxec pour la commande a exec,
// et les sort de la liste chainee ( file, - flag et autre mots pour grep)
int	size_args(t_list *l_token)
{
	int			size;
	t_list		*tmp_token;

	size = 2;
	tmp_token = l_token;
	if (l_token->next && (ft_strncmp(l_token->content, "<", 1) == 0 || \
	(ft_strncmp(l_token->content, ">", 1) == 0)))
		size ++;
	else
	{	
		while (tmp_token->next && (!is_operator(tmp_token->next)))
		{
			size++;
			tmp_token = tmp_token->next;
		}
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
	args_exec = malloc(sizeof(char *) * size);
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
