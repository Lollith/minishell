/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:25:45 by frrusso           #+#    #+#             */
/*   Updated: 2022/08/08 10:45:41 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 0 in not a builtins
// 1 is a builtins
int	ft_builtins_fork(char **line)
{
	if (ft_is_str(line[0], "echo") || ft_is_str(line[0], "say"))
		return (1);
	if (ft_is_str(line[0], "cd"))
		return (1);
	if (ft_is_str(line[0], "pwd"))
		return (1);
	if (ft_is_str(line[0], "export"))
		return (1);
	if (ft_is_str(line[0], "unset"))
		return (1);
	if (ft_is_str(line[0], "env"))
		return (1);
	if (ft_is_str(line[0], "exit") || ft_is_str(line[0], "quit"))
		return (1);
	return (0);
}

// 0 in not a builtins
// 1 is a builtins
// 2 exit
int	ft_builtins(char **line, char ***envp, t_list *l_token, t_pipe *pipex)
{
	if (ft_is_str(line[0], "echo") || ft_is_str(line[0], "say"))
		return (ft_echo(line));
	if (ft_is_str(line[0], "cd"))
		return (ft_cd(line, envp));
	if (ft_is_str(line[0], "pwd"))
		return (ft_pwd(*envp));
	if (ft_is_str(line[0], "export"))
		return (ft_export(line, envp));
	if (ft_is_str(line[0], "unset"))
		return (ft_unset(line, envp));
	if (ft_is_str(line[0], "env"))
		return (ft_env(*envp));
	if (ft_is_str(line[0], "exit") || ft_is_str(line[0], "quit"))
		return (ft_exit(line, *envp, l_token, pipex));
	return (0);
}

void	ft_quoting_input(char const *str, char *res)
{
	int		i;
	int		size;

	size = 0;
	i = -1;
	while (str[++i])
	{
		if (ft_d_quote(str, res, &i, size) || ft_s_quote(str, res, &i, size))
			continue ;
		ft_quoting_res(str, res, &i, &size);
	}
	res[i + size] = '\0';
}

char	*ft_quoting(char const *str)
{
	int		i;
	int		size;
	int		agouet;
	char	*res;

	size = 1;
	i = -1;
	while (str[++i])
	{
		if (ft_quoting_quote(str, &i, '\"') || ft_quoting_quote(str, &i, '\''))
			continue ;
		agouet = ft_quoting_quoting(str, &i);
		if (agouet == 3)
			return (NULL);
		size += agouet;
	}
	res = malloc(sizeof(char) * (i + size));
	if (!res)
		return (NULL);
	ft_quoting_input(str, res);
	return (res);
}

void	free_content(t_pipe *pipex)
{
	free(pipex->l_start->content);
	free(pipex->l_start);
}
