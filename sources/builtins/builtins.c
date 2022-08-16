/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:44:51 by frrusso           #+#    #+#             */
/*   Updated: 2022/08/08 18:01:55 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **line, char **envp, t_pipe *pipex)
{
	int	ret;

	if (ft_string_of_string_len(line) > 3)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
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
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(line[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	else
		exit(ft_exit_free(line, envp, pipex));
	return (1);
}

int	ft_echo(char **line)
{
	int	i;

	i = 1;
	while (ft_echo_cheak(line[i]))
		i++;
	while (line[i])
	{
		if (!line[i][0])
			write(1, " ", 1);
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

int	ft_cd(char **line, char ***envp)
{
	char	**bis;

	if (ft_string_of_string_len(line) >= 4)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 1);
		return (1);
	}
	bis = ft_export_line("OLDPWD=");
	if (!bis)
		return (2);
	if (ft_cd_exec(line, envp, bis))
		return (1);
	if (ft_export(bis, envp) == 2)
		return (2);
	ft_split_free(bis);
	bis = ft_export_line("PWD=");
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
