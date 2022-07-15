/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 15:06:15 by frrusso           #+#    #+#             */
/*   Updated: 2022/07/15 15:06:18 by frrusso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env_size(char const *str)
{
	int		var;
	char	name[BUFFER_NAME];
	char	*value;

	var = 0;
	while (ft_isalnum(str[var]))
		var++;
	ft_memcpy(name, str, var);
	name[var] = '\0';
	value = getenv(name);
	if (value)
		return (ft_strlen(value));
	return (0);
}

char	*ft_realloc_token(char *token)
{
	int		i;
	int		size;
	char	*res;

	size = 0;
	i = -1;
	while (token[++i])
	{
		if (token[i] != '$')
			size++;
		else
		{
			i++;
			size += ft_env_size(token + i);
		}
	}
}

int	ft_env_var(char ***token, char **envp)
{
	int		i;
	int		j;

	j = -1;
	while (token[0][++j])
	{
		i = -1;
		while (token[0][j][++i])
		{
			if (token[0][j][i] == '$')
			{
				token[0][j] = ft_realloc_token(token[0][j]);
				if (!token)
					return (1);
			}
		}
	}
	return (0);
}