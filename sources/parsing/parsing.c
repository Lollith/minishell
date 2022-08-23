/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 10:08:20 by agouet            #+#    #+#             */
/*   Updated: 2022/08/18 17:35:36 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_quote_norm(int n, t_pipe *pipex)
{
	if (n == 0)
		ft_msg("minishell: \'\': Command not found.\n", STDERR_FILENO);
	else
		ft_msg("minishell: \'..\': Command not found.\n", STDERR_FILENO);
	pipex->pipe_ret = 127;
}

int	ft_quote(char *line, t_pipe *pipex)
{
	int	i;
	int	n;
	int	two;
	int	one;

	if (!line)
		return (FALSE);
	n = 0;
	two = 0;
	one = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == '\"')
			two++;
		else if (line[i] == '\'')
			one++;
		else if (!ft_is_space(line[i], MS_SPACE))
			n++;
	}
	if (n == 0 || ft_is_str(line, ".."))
		ft_quote_norm(n, pipex);
	if (two % 2 == 1 || one % 2 == 1 || n == 0 || ft_is_str(line, ".."))
		return (FALSE);
	return (TRUE);
}

// fonction qui cree les "mots" en fonction des espaces
// token est free dans minishell par ft_free_split
char	**lexer(char *line, t_pipe *pipex)
{
	char	**token;
	char	*str;

	if (!ft_quote(line, pipex))
		return (NULL);
	str = ft_quoting(line, pipex);
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
	int	size;

	size = 2;
	if (l_token->next && (ft_strncmp(l_token->content, "<", 1) == 0 || \
	(ft_strncmp(l_token->content, ">", 1) == 0)))
		size++;
	else
	{
		while (l_token->next && (!is_operator(l_token->next)))
		{
			size++;
			l_token = l_token->next;
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
	if (!size)
		return (NULL);
	args_exec = malloc(sizeof(char *) * size);
	if (!args_exec)
		return (FAILURE);
	args_exec[0] = ft_strdup((l_token)->content);
	i = 1;
	while (l_token && i < size - 1)
	{
		args_exec[i] = ft_strdup((l_token)->next->content);
		i++;
		ft_l_delete(l_token);
	}
	args_exec[size - 1] = NULL;
	return (args_exec);
}
