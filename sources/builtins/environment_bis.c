/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lollith <lollith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:54:59 by frrusso           #+#    #+#             */
/*   Updated: 2022/08/27 14:34:12 by lollith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export_norm(char ***res, char ***envp)
{
	ft_split_free(envp[0]);
	envp[0] = res[0];
}

// Change variable
int	ft_export_value(char **line, char ***envp, int i)
{
	free(envp[0][i]);
	envp[0][i] = malloc(sizeof(char) * (ft_strlen(line[1]) + 1));
	if (!envp[0][i])
		return (1);
	ft_memcpy(envp[0][i], line[1], ft_strlen(line[1]) + 1);
	return (0);
}

// New variable
char	**ft_export_envp(char **line, char **envp)
{
	int		i;
	char	**res;

	res = malloc(sizeof(char *) * (ft_string_of_string_len(envp) + 1));
	if (!res)
		return (NULL);
	i = -1;
	while (envp[++i])
	{
		res[i] = malloc(sizeof(char) * (ft_strlen(envp[i]) + 1));
		if (!res[i])
			return (NULL);
		ft_memcpy(res[i], envp[i], ft_strlen(envp[i]) + 1);
	}
	res[i] = malloc(sizeof(char) * (ft_strlen(line[1]) + 1));
	if (!res[i])
		return (NULL);
	ft_memcpy(res[i], line[1], ft_strlen(line[1]) + 1);
	res[i + 1] = NULL;
	return (res);
}

int	ft_echo_cheak(char *line)
{
	int	i;

	if (!line || line[0] != '-')
		return (0);
	i = 1;
	while (line[i] && line[i] == 'n')
		i++;
	if (line[i] || i == 1)
		return (0);
	return (1);
}

int	ft_exit_free(char **line, char **envp, t_pipe *pipex)
{
	close(pipex->tmp_in);
	close(pipex->tmp_out);
	rl_clear_history();
	ft_split_free(line);
	ft_split_free(envp);
	ft_child_close_pipe(pipex);
	ft_lstclear2(&pipex->l_start);
	write(1, "exit\n", 5);
	if (g_sig == 1)
		return (130);
	return (pipex->pipe_ret);
}
