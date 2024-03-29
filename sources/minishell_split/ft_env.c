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

int	ft_env_size(char const *token, int i, char **envp)
{
	int		var;
	char	name[BUFFER_NAME];
	char	*value;

	i++;
	var = 0;
	while (ft_isalnum(token[i + var]))
		var++;
	if (var == 0)
		return (0);
	if (var >= BUFFER_NAME)
		return (ft_msg("Your environment name is too long", 2));
	ft_memcpy(name, token + i, var);
	name[var] = '\0';
	value = ft_getenv(name, envp);
	if (value)
		return (ft_strlen(value));
	return (0);
}

int	ft_env_input_var(char const *str, char *res, int j, char **envp)
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
	value = ft_getenv(name, envp);
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

void	ft_env_input(char *token, char *res, int pipe_ret, char **envp)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (token[++i])
	{
		if (token[i] == '\'' || token[i] == '\"')
			ft_env_input_single(token, res, &i, &j);
		else
		{
			if (token[i] != '$' || (token[i] == '$' && \
			!ft_isalnum(token[i + 1]) && token[i + 1] != '?'))
				res[j] = token[i];
			else if (token[i] == '$' && token[i + 1] == '?')
				ft_env_pipe_input(res, pipe_ret, &i, &j);
			else
			{
				j = ft_env_input_var(token + ++i, res, j, envp);
				i = ft_env_input_double(token, i);
			}
			j++;
		}
	}
}

char	*ft_env_realloc_token(char *token, int pipe_ret, char **envp)
{
	int		i;
	int		size;
	char	*res;

	size = 1;
	i = -1;
	while (token[++i])
	{
		if (token[i] == '\'')
		{
			while (token[++i] != '\'')
				size++;
		}
		else
			size += ft_env_double_quote(token, pipe_ret, envp, &i);
	}
	res = malloc(sizeof(char) * size);
	if (!res)
		return (NULL);
	ft_env_input(token, res, pipe_ret, envp);
	res[size - 1] = '\0';
	return (res);
}

int	ft_env_var(char ***token, int pipe_ret, t_list *l_token, char **envp)
{
	int		i;
	int		j;
	void	*tmp1;
	void	*tmp2;

	j = -1;
	while (token[0][++j])
	{
		i = -1;
		while (token[0][j][++i])
		{
			if (ft_is_space(token[0][j][i], "$\"\'"))
			{
				tmp1 = token[0][j];
				tmp2 = ft_env_realloc_token(token[0][j], pipe_ret, envp);
				if (!tmp2)
					return (1);
				ft_env_free(tmp1, tmp2, l_token);
				token[0][j] = tmp2;
				break ;
			}
		}
	}
	return (0);
}
