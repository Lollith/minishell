/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 13:21:57 by frrusso           #+#    #+#             */
/*   Updated: 2022/05/26 13:22:01 by frrusso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_str(char *line, char *str)
{
	int		i;

	if (!line || !str)
		return (0);
	if (ft_strlen(line) != ft_strlen(str))
		return (0);
	i = 0;
	while (str[i] && line[i] == str[i])
		i++;
	if (!str[i] && !line[i])
		return (1);
	return (0);
}
