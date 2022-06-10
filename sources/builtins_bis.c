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
		res[i] = malloc(sizeof(char) * (ft_strlen(envp[i]) + 1));
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
	(void)line;
	ft_print_string_of_string(envp);
	return (1);
}

int	ft_unset_parsing(char **line)
{
	int		i;
	char	*str;

	if (!line[1])
		return (1);
	i = 0;
	while (line[1][i])
	{
		if (line[1][i] == '=')
		{
			str = ft_strjoin("minishell: unset: \"", line[1]);
			str = ft_strjoin_free(str, "\": not a valid identifier");
			write(1, str, ft_strlen(str));
			free(str);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_unset(char **line, char ***envp)
{
	int		i;
	int		len;

	if (!line || !envp || ft_unset_parsing(line))
		return (1);
	len = ft_strlen(line[1]);
	i = 0;
	while (envp[0][i] && ft_strncmp(envp[0][i], line[1], len))
		i++;
	if (*envp[i])
	{
		*envp = ft_unset_envp(line, *envp);
		if (!*envp)
			return (2);
	}
	return (1);
}

int	ft_env(char **envp)
{
	ft_print_string_of_string(envp);
	return (1);
}
