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
	if (var == 0)
		return (0);
	if (var >= BUFFER_NAME)
	{
		ft_msg("Your environment name is too long", 2);
		return (0);
	}
	ft_memcpy(name, str, var);
	name[var] = '\0';
	value = getenv(name);
	if (value)
		return (ft_strlen(value));
	return (0);
}

int	ft_env_input_var(char const *str, char *res, int j)
{
	int		i;
	int		var;
	char	name[BUFFER_NAME];
	char	*value;

	var = 0;
	while (ft_isalnum(str[var]))
		var++;
	if (var == 0 || var >= BUFFER_NAME)
		return (j - 1);
	ft_memcpy(name, str, var);
	name[var] = '\0';
	value = getenv(name);
	if (!value)
		return (j - 1);
	i = -1;
	while (value[++i])
	{
		res[j] = value[i];
		j++;
	}
	return (j - 1);
}

void	ft_env_input(char *token, char *res, int pipe_ret)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (token[++i])
	{
		if (token[i] != '$')
			res[j] = token[i];
		else if (token[i + 1] == '?')
			ft_env_pipe_input(res, pipe_ret, &i, &j);
		else
		{
			i++;
			j = ft_env_input_var(token + i, res, j);
			while (ft_isalnum(token[i]))
				i++;
			i--;
		}
		j++;
	}
	res[j] = '\0';
	free(token);
}

char	*ft_env_realloc_token(char *token, int pipe_ret)
{
	int		i;
	int		size;
	char	*res;

	size = 1;
	i = -1;
	while (token[++i])
	{
		if (token[i] != '$')
			size++;
		else if (token[i + 1] == '?')
			size += ft_env_pipe_size(pipe_ret, &i);
		else
		{
			i++;
			size += ft_env_size(token + i);
			while (ft_isalnum(token[i + 1]))
				i++;
		}
	}
	res = malloc(sizeof(char) * size);
	if (!res)
		return (NULL);
	ft_env_input(token, res, pipe_ret);
	return (res);
}

int	ft_env_var(char ***token, int pipe_ret)
{
	int	i;
	int	j;

	j = -1;
	while (token[0][++j])
	{
		i = -1;
		while (token[0][j][++i])
		{
			if (token[0][j][i] == '$')
			{
				token[0][j] = ft_env_realloc_token(token[0][j], pipe_ret);
				if (!token)
					return (1);
			}
		}
	}
	return (0);
}
