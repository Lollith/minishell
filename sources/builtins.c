/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:44:51 by frrusso           #+#    #+#             */
/*   Updated: 2022/05/27 13:44:54 by frrusso          ###   ########.fr       */
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

// need to add relative path
int	ft_cd(char **line)
{
	if (line[1])
		chdir(line[1]);
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

int	ft_export(void)
{
	return (1);
}
