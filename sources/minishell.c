/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:25:45 by frrusso           #+#    #+#             */
/*   Updated: 2022/05/23 13:25:51 by frrusso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_split(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

// 0 in not a builtins
// 1 is a builtins
// 2 exit
int	ft_builtins(char *line)
{
	if (ft_is_str(line, "echo"))
		return (1);
	if (ft_is_str(line, "cd"))
		return (1);
	if (ft_is_str(line, "pwd"))
		return (1);
	if (ft_is_str(line, "export"))
		return (1);
	if (ft_is_str(line, "unset"))
		return (1);
	if (ft_is_str(line, "env"))
		return (1);
	if (ft_is_str(line, "exit"))
		return (2);
	return (0);
}

int	minishell(char *line, char **envp)
{
	int		i;
	int		in;
	char	**cmd;
	char	**token;

	cmd = ft_split(line, ';');
	if (!cmd)
		return (0);
	in = 0;
	i = -1;
	while (cmd[++i] && in != 2)
	{
		token = lexer(cmd[i]);
		if (!token)
			break ;
		in = ft_builtins(token[0]);
		if (in > 0)
			continue ;
		ft_exec(envp, token);
		ft_free_split(token);
	}
	if (in == 2)
		ft_free_split(token);
	ft_free_split(cmd);
	return (in);
}
