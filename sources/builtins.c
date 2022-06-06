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

int	ft_echo(char **line)
{
	int	i;

	i = 1;
	if (ft_is_str(line[1], "-n"))
		i++;
	while (line[i])
	{
		printf("%s", line[i]);
		i++;
	}
	if (!ft_is_str(line[1], "-n"))
		printf("\n");
	return (1);
}

char	*get_home(char **envp)
{
	int		i;
	char	*home;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "HOME=", 5))
		i++;
	home = envp[i] + 5;
	return (home);
}

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
