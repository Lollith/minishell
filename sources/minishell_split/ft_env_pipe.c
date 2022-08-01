/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:25:59 by frrusso           #+#    #+#             */
/*   Updated: 2022/07/21 12:26:01 by frrusso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env_pipe_size(int pipe_ret, int *i)
{
	int	res;

	i[0] += 1;
	res = 0;
	if (ft_isneg(pipe_ret))
	{
		res = 1;
		pipe_ret = -pipe_ret;
	}
	res += ft_dsize(pipe_ret);
	return (res);
}

void	ft_env_pipe_input(char *res, int pipe_ret, int *i, int *j)
{
	int		k;
	char	*pipe;

	pipe = ft_itoa(pipe_ret);
	k = -1;
	while (pipe[++k])
	{
		res[*j] = pipe[k];
		j[0] += 1;
	}
	j[0] -= 1;
	i[0] += 1;
	free(pipe);
}
