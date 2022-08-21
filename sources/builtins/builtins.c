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
	else
	{
		pipex->pipe_ret = 0;
		exit(ft_exit_free(line, envp, pipex));
	}
	return (1);
}

int	ft_echo(char **line, char **envp)
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
			ft_putstr_fd(ft_get_home(envp), 1);
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
	return (1);
}

char	*ft_get_home(char **envp)
{
	int		i;
	char	*home;

	home = NULL;
	i = 0;
	while (envp[i] && (ft_strncmp(envp[i], "HOME", 4) != 0))
		i++;
	if (envp[i])
		home = envp[i] + 5;
	else
		ft_putstr_fd("minishell: cd: HOME not set\n", 1);
	return (home);
}

int	ft_cd(char **line, char ***envp, t_pipe *pipex)
{
	char	**bis;

	if (ft_string_of_string_len(line) >= 4)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 1);
		pipex->pipe_ret_b = 1;
		return (1);
	}
	bis = ft_export_line("OLDPWD=", line[1]);
	if (!bis)
		return (2);
	if (ft_cd_exec(line, envp, bis, pipex))
		return (1);
	if (ft_export(bis, envp) == 2)
		return (2);
	ft_split_free(bis);
	bis = ft_export_line("PWD=", NULL);
	if (!bis || ft_export(bis, envp) == 2)
		return (2);
	ft_split_free(bis);
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
