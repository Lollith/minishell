/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:12:59 by frrusso           #+#    #+#             */
/*   Updated: 2022/08/10 17:13:01 by frrusso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env_input_single(char *token, char *res, int *i, int *j)
{
	static int	x = 0;

	if (token[*i] == '\"')
		x = 1 - x;
	if (x == 1)
		return ;
	while (token[++(*i)] != '\'')
	{
		res[*j] = token[*i];
		(*j)++;
	}
}

int	ft_env_input_double(char *token, int i)
{
	while (ft_isalnum(token[i]))
		i++;
	i--;
	return (i);
}

int	ft_env_double_quote_bis(char *token, char **envp, int *i)
{
	int		size;

	size = 0;
	size += ft_env_size(token, *i, envp);
	while (ft_isalnum(token[(*i) + 1]))
		(*i)++;
	return (size);
}

int	ft_env_double_quote(char *token, int pipe_ret, char **envp, int *i)
{
	int		size;

	size = 0;
	if (!ft_is_space(token[*i], "$\""))
		size++;
	else if (token[*i] == '$' && token[(*i) + 1] == '?')
		size += ft_env_pipe_size(pipe_ret, i);
	else if (token[*i] == '$')
		size += ft_env_double_quote_bis(token, envp, i);
	else if (token[*i] == '\"')
	{
		while (token[++(*i)] != '\"')
		{
			if (token[*i] != '$')
				size++;
			else if (token[*i] == '$' && token[(*i) + 1] == '?')
				size += ft_env_pipe_size(pipe_ret, i);
			else if (token[*i] == '$')
				size += ft_env_double_quote_bis(token, envp, i);
		}
	}
	return (size);
}
