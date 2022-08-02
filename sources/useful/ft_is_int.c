/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:56:18 by frrusso           #+#    #+#             */
/*   Updated: 2022/08/02 14:56:20 by frrusso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_big(char *line)
{
	int		i;
	char	*max;

	i = 0;
	while (line[i] && i <= 11)
		i++;
	if (i < 10 || (i == 10 && (line[0] == 43 || line[0] == 45)))
		return (0);
	if (i > 11 || (i == 11 && ft_isdigit(line[0])))
		return (1);
	if (line[0] == '-')
		max = "2147483648";
	else
		max = "2147483647";
	if (line[0] == 43 || line[0] == 45)
		line++;
	i = 11;
	while (--i && *line >= *max)
	{
		if (*line > *max)
			return (1);
		line++;
		max++;
	}
	return (0);
}

int	ft_is_newint(char *line)
{
	int	i;

	i = 0;
	if (line[i])
	{
		if (ft_isdigit(line[i]))
			i++;
		else if ((line[i] == 43 || line[i] == 45) && ft_isdigit(line[i + 1]))
			i++;
		else
			return (1);
	}
	while (line[i])
	{
		if (ft_isdigit(line[i]))
			i++;
		else
			return (1);
	}
	return (0);
}

int	ft_is_int(char *line)
{
	if (ft_is_newint(line))
		return (0);
	if (ft_is_big(line))
		return (0);
	return (1);
}
