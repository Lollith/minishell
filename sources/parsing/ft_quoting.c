/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quoting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 14:08:36 by frrusso           #+#    #+#             */
/*   Updated: 2022/08/19 08:57:23 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_quoting_quote(char const *str, int *i, char c)
{
	if (str[*i] == c)
	{
		*i += 1;
		while (str[*i] != c)
			*i += 1;
		return (TRUE);
	}
	return (FALSE);
}

int	ft_quoting_quoting(char const *str, int *i, t_pipe *pipex)
{
	int	j;

	if (ft_is_space(str[*i], "&|><"))
	{
		if (str[*i] == '&' && str[*i + 1] != '&')
		{
			putsr_ret (pipex, "minishell: syntax error near unexpected token\n");
			return (3);
		}
		if ((str[*i] == '&' && str[*i + 1] == '&') || \
		(str[*i] == '|' && str[*i + 1] == '|') || \
		(str[*i] == '>' && str[*i + 1] == '>') || \
		(str[*i] == '<' && str[*i + 1] == '<'))
			*i += 1;
		j = *i + 1;
		while (str[j] == '\"' || str[j] == '\'')
			j++;
		if (!str[j] || ft_is_space(str[*i + 1], "&|><"))
		{
			putsr_ret (pipex, "minishell: syntax error near unexpected token\n");
			return (3);
		}
		return (2);
	}
	return (0);
}

int	ft_d_quote(char const *str, char *res, int *i, int size)
{
	if (str[*i] == '\"')
	{
		res[*i + size] = '\"';
		*i += 1;
		while (str[*i] != '\"')
		{
			res[*i + size] = str[*i];
			*i += 1;
		}
		res[*i + size] = '\"';
		return (TRUE);
	}
	return (FALSE);
}

int	ft_s_quote(char const *str, char *res, int *i, int size)
{
	if (str[*i] == '\'')
	{
		res[*i + size] = '\'';
		*i += 1;
		while (str[*i] != '\'')
		{
			res[*i + size] = str[*i];
			*i += 1;
		}
		res[*i + size] = '\'';
		return (TRUE);
	}
	return (FALSE);
}

void	ft_quoting_res(char const *str, char *res, int *i, int *size)
{
	if (ft_is_space(str[*i], "&|><"))
	{
		res[*i + *size] = ' ';
		*size += 1;
		res[*i + *size] = str[*i];
		if (ft_is_space(str[*i + 1], "&|><"))
		{
			*i += 1;
			res[*i + *size] = str[*i];
		}
		*size += 1;
		res[*i + *size] = ' ';
	}
	else
		res[*i + *size] = str[*i];
}
