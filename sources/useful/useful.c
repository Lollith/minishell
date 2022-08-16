/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 13:21:33 by frrusso           #+#    #+#             */
/*   Updated: 2022/08/08 11:17:31 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_realloc_envp(char **envp)
{
	int		i;
	int		j;
	char	**res;

	res = malloc(sizeof(char *) * ft_string_of_string_len(envp));
	if (!res)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		res[i] = malloc(sizeof(char) * (ft_strlen(envp[i]) + 1));
		if (!res[i])
			return (NULL);
		j = 0;
		while (envp[i][j])
		{
			res[i][j] = envp[i][j];
			j++;
		}
		res[i][j] = '\0';
		i++;
	}
	res[i] = NULL;
	return (res);
}

int	ft_msg(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
	return (FAILURE);
}

int	ft_msg_perror(char *origin)
{
	perror(origin);
	exit(FAILURE);
}

int	ft_string_of_string_len(char **tab)
{
	int	i;

	if (!tab)
		return (0);
	i = 0;
	while (tab[i])
		i++;
	return (i + 1);
}

void	ft_print_string_of_string(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}
