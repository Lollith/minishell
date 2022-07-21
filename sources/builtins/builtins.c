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
	if (ft_is_str(line[1], "-n"))
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
	if (!ft_is_str(line[1], "-n"))
		write(1, "\n", 1);
	return (1);
}

char	*get_home(char **envp)
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

// create OLDPWD
int	ft_cd(char **line, char **envp)
{
	char	*home;

	home = get_home(envp);
	if (line[1])
		chdir(line[1]);
	else
		chdir(home);
	return (1);
}

int	ft_pwd(void)
{
	char	cwd[256];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd() error");
	else
		printf("%s\n", cwd);
	return (1);
}
