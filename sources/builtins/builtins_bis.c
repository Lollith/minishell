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

	res = malloc(sizeof(char *) * ft_string_of_string_len(envp));
	if (!res)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		res[i] = malloc(sizeof(char) * (ft_strlen(envp[i]) + 1));
		if (!res[i])
			return (NULL);
		j = 0;
		while (envp[i][j])
		{
			res[i][j] = envp[i][j];
			j++;
		}
		res[i][j] = '\0';
		i++;
	}
	res[i] = NULL;
	return (res);
}

int	ft_env_parsing(char **line, int is_unset)
{
	int		i;

	if (!line[1])
		return (is_unset);
	i = 0;
	while (line[1][i])
	{
		if (line[1][i] == '=')
		{
			if (is_unset)
			{
				ft_putstr_fd("minishell: unset: \'", 2);
				ft_putstr_fd(line[1], 2);
				ft_putstr_fd("\': not a valid identifier\n", 2);
			}
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

int	ft_export(char **line, char ***envp)
{
	int		i;
	char	**res;

	if (!ft_env_parsing(line, 0))
		return (1);
	i = 0;
	while (envp[0][i] && \
	(ft_strncmp(envp[0][i], line[1], ft_strlen_equal(envp[0][i]))) != 0)
		i++;
	if (envp[0][i])
	{
		if (ft_export_value(line, envp, i))
			return (2);
	}
	else
	{
		res = ft_export_envp(line, envp[0]);
		if (!res)
			return (2);
		ft_split_free(envp[0]);
		envp[0] = res;
	}
	return (1);
}

int	ft_unset(char **line, char ***envp)
{
	int		i;
	char	**res;

	if (ft_env_parsing(line, 1))
		return (1);
	i = 0;
	while (envp[0][i] && \
	(ft_strncmp(envp[0][i], line[1], ft_strlen_equal(envp[0][i]))) != 0)
		i++;
	if (envp[0][i])
	{
		res = ft_unset_envp(line, envp[0]);
		if (!res)
			return (2);
		ft_split_free(envp[0]);
		envp[0] = res;
	}
	return (1);
}

int	ft_env(char **envp)
{
	ft_print_string_of_string(envp);
	return (1);
}
