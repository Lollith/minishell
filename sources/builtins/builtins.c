/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:44:51 by frrusso           #+#    #+#             */
/*   Updated: 2022/06/06 10:08:44 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(void)
{
	write(1, "exit\n", 5);
	exit(0);
	return (2);
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
	while (envp[i] && ft_strncmp(envp[i], "HOME=", 5))
		i++;
	if (envp[i])
		home = envp[i] + 5;
	return (home);
}

int	ft_cd(char **line, char ***envp)
{
	int		ret;
	char	**bis;

	bis = ft_export_line("OLDPWD=");
	if (!bis)
		return (2);
	if (line[1])
		ret = chdir(line[1]);
	else
		ret = chdir(ft_get_home(*envp));
	if (ret < 0)
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

int	ft_pwd(void)
{
	char	cwd[256];
	char	*value;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		value = getenv("PWD");
		if (value)
			printf("%s\n", value);
		else
			ft_putstr_fd("pwd: cannot find current directory\n", 2);
	}
	else
		printf("%s\n", cwd);
	return (1);
}
