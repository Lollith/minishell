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

int	ft_env_parsing_empty(int is_unset)
{
	if (is_unset)
		printf("minishell: unset: \'\': not a valid identifier\n");
	else
		printf("minishell: export: \'\': not a valid identifier\n");
	return (is_unset);
}

int	ft_env_parsing(char **line, int is_unset)
{
	int	i;

	if (!line[1])
		return (is_unset);
	if (!line[1][0])
		return (ft_env_parsing_empty(is_unset));
	if (!is_unset && line[1][0] == '=')
	{
		printf("minishell: export: \'%s\': not a valid identifier\n", line[1]);
		return (FALSE);
	}
	i = 0;
	while (line[1][i] && line[1][i] != '=')
		i++;
	if (line[1][i] == '=')
	{
		if (is_unset)
			printf("minishell: unset: \'%s\': not a valid identifier\n", line[1]);
		return (TRUE);
	}
	return (FALSE);
}

int	ft_export(char **line, char ***envp)
{
	int		i;
	char	**res;

	if (!line[1])
		ft_print_string_of_string(*envp);
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
	int		j;
	char	**res;
	char	*tmp;

	tmp = line[1];
	j = 1;
	while (line[1])
	{
		if (!ft_env_parsing(line, 1))
		{
			i = ft_unset_i(line, envp);
			if (envp[0][i])
			{
				res = ft_unset_envp(line, envp[0]);
				if (!res)
					return (2);
				ft_split_free(envp[0]);
				envp[0] = res;
			}
		}
		line[1] = line[++j];
	}
	line[1] = tmp;
	return (1);
}

int	ft_env(char **envp)
{
	ft_print_string_of_string(envp);
	return (1);
}
