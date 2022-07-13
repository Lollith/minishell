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

int	ft_link_fd(int pipefd0, int pipefd1, int std)
{
	if (close(pipefd0) < 0)
		return (msg_perror("pipefd0 "));
	if (dup2(pipefd1, std) == -1)
		return (msg_perror("dup2 "));
	if (close(pipefd1) < 0)
		return (msg_perror("pipefd1 "));
	return (SUCCESS);
}