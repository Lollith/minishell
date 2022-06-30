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

int	ft_builtins_ret(char **line, char ***envp)
{
	if (ft_is_str(line[0], "echo") || ft_is_str(line[0], "cd"))
		return (1);
	if (ft_is_str(line[0], "pwd") || ft_is_str(line[0], "export"))
		return (1);
	if (ft_export(line, envp) || ft_is_str(line[0], "unset"))
		return (1);
	if (ft_is_str(line[0], "env"))
		return (1);
	if (ft_is_str(line[0], "exit"))
		return (2);
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

// int	minishell(char *line, char ***envp)
// {
// 	int		i;
// 	int		in;
// 	char	**cmd;
// 	char	**token;

// 	cmd = ft_split(line, ';');
// 	if (!cmd)
// 		return (0);
// 	in = 0;
// 	token = NULL;
// 	i = -1;
// 	while (cmd[++i] && in != 2)
// 	{
// 		ft_split_free(token);
// 		token = lexer(cmd[i]);
// 		if (!token)
// 			break ;
// 		in = ft_builtins(token, envp);
// 		if (in > 0)
// 			continue ;
// 		// execve
// 	}
// 	ft_split_free(token);
// 	ft_split_free(cmd);
// 	return (in);
// }
