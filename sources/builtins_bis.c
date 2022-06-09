/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:14:24 by frrusso           #+#    #+#             */
/*   Updated: 2022/05/27 17:14:26 by frrusso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_realloc_envp(char **envp)
{
	int		i;
	int		j;
	char	**res;

	if (!envp)
		return (NULL);
	res = malloc(sizeof(char *) * ft_string_of_string_len(envp));
	if (!res)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		res[i] = malloc(sizeof(char) * (ft_strlen(envp[i] + 1)));
		if (!res[i])
			return (NULL);
		j = 0;
		while (envp[i][j])
		{
			res[i][j] = envp[i][j];
			j++;
		}
		i++;
	}
	return (res);
}

int	ft_export(char **line, char **envp)
{
	printf("%p\n", line[0]);
	printf("%p\n", envp);
	return (1);
}

int	ft_unset(char **line, char **envp)
{
	printf("%p\n", line[0]);
	printf("%p\n", envp);
	return (1);
}

int	ft_env(char **envp)
{
	ft_print_string_of_string(envp);
	return (1);
}
