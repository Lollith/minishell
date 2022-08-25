/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lollith <lollith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:44:51 by frrusso           #+#    #+#             */
/*   Updated: 2022/08/21 13:35:22 by lollith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **line, char **envp, t_pipe *pipex)
{
	int	ret;

	if (pipex->nb_pipes_const != 0)
		return (1);
	if (ft_string_of_string_len(line) > 3)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		pipex->pipe_ret_b = 1;
		return (1);
	}
	if (line[1])
	{
		if (ft_is_int(line[1]))
		{
			ret = ft_atoi(line[1]);
			ft_exit_free(line, envp, pipex);
			exit (ret);
		}
		putstr_exit(line, pipex);
		exit(ft_exit_free(line, envp, pipex));
	}
	pipex->pipe_ret = 0;
	exit(ft_exit_free(line, envp, pipex));
	return (1);
}

int	ft_echo(char **line, char **envp, t_pipe *pipex)
{
	int	i;

	i = 1;
	while (ft_echo_cheak(line[i]))
		i++;
	while (line[i])
	{
		if (!line[i][0])
			write(1, " ", 1);
		if (line[i][0] == '~')
		{
			ft_putstr_fd(ft_cd_get_home(envp, 0), 1);
			ft_putstr_fd(line[i] + 1, 1);
		}
		else
			ft_putstr_fd(line[i], 1);
		if (line[i + 1] && line[i][0] != '\0')
			write(1, " ", 1);
		i++;
	}
	if (!ft_echo_cheak(line[1]))
		write(1, "\n", 1);
	pipex->pipe_ret = 0;
	return (1);
}

int	ft_pwd(char **envp)
{
	char	cwd[256];
	char	*value;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		value = ft_getenv("PWD", envp);
		if (value)
			printf("%s\n", value);
		else
			ft_putstr_fd("pwd: cannot find current directory\n", 2);
	}
	else
		printf("%s\n", cwd);
	return (1);
}

int	ft_export_init(char **line, char ***envp, char **tmp)
{
	if (!line[1])
		ft_print_string_of_string(*envp);
	*tmp = line[1];
	return (0);
}

int	ft_unset_i(char **line, char ***envp)
{
	int	i;

	i = 0;
	while (envp[0][i] && \
	(ft_strncmp(envp[0][i], line[1], ft_strlen_equal(envp[0][i]))) != 0)
		i++;
	return (i);
}
