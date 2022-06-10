/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:02:36 by frrusso           #+#    #+#             */
/*   Updated: 2022/06/09 16:02:39 by frrusso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_unset_envp(char **line, char **envp)
{
	int		i;
	int		j;
	int		k;
	char	**res;

	res = malloc(sizeof(char *) * (ft_string_of_string_len(envp) - 1));
	if (!res)
		return (NULL);
	k = 0;
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], line[1], ft_strlen(line[1])) == 0)
		{
			k++;
			continue ;
		}
		res[i - k] = malloc(sizeof(char) * (ft_strlen(envp[i]) + 1));
		if (!res[i - k])
			return (NULL);
		j = -1;
		while (envp[i][++j])
			res[i - k][j] = envp[i][j];
	}
	return (res);
}
