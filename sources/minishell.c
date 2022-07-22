/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:25:45 by frrusso           #+#    #+#             */
/*   Updated: 2022/06/23 15:54:38 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 0 in not a builtins
// 1 is a builtins
int	ft_builtins_fork(char **line)
{
	if (ft_is_str(line[0], "echo"))
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
	if (ft_is_str(line[0], "exit"))
		return (1);
	return (0);
}

// 0 in not a builtins
// 1 is a builtins
// 2 exit
int	ft_builtins(char **line, char ***envp)
{
	if (ft_is_str(line[0], "echo"))
		return (ft_echo(line));
	if (ft_is_str(line[0], "cd"))
		return (ft_cd(line, *envp));
	if (ft_is_str(line[0], "pwd"))
		return (ft_pwd());
	if (ft_is_str(line[0], "export"))
		return (ft_export(line, envp));
	if (ft_is_str(line[0], "unset"))
		return (ft_unset(line, envp));
	if (ft_is_str(line[0], "env"))
		return (ft_env(*envp));
	if (ft_is_str(line[0], "exit"))
		return (ft_exit());
	return (0);
}

char	**create_token_exec(char *cmd)
{
	char	**new_token_exec;

	new_token_exec = malloc(sizeof(char *) * 2);
	if (!new_token_exec)
		return (NULL);
	new_token_exec[0] = cmd;
	new_token_exec[1] = NULL;
	return (new_token_exec);
}

char	*ft_quoting(char const *str)
{
	int		i;
	int		size;
	char	*res;

	size = 1;
	i = -1;
	while (str[++i])
	{
		if (ft_quoting_quote(str, &i, '\"') || ft_quoting_quote(str, &i, '\''))
			continue ;
		if (ft_quoting_quoting(str, &i) == 1)
			return (NULL);
		else
			size += ft_quoting_quoting(str, &i);
	}
	res = malloc(sizeof(char) * (i + size));
	if (!res)
		return (NULL);
	size = 0;
	i = -1;
	while (str[++i])
	{
		if (ft_d_quote(str, res, &i, size) || ft_s_quote(str, res, &i, size))
			continue ;
		ft_quoting_res(str, res, &i, &size);
	}
	res[i + size] = '\0';
	return (res);
}
