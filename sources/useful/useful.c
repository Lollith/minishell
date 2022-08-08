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

int	ft_free_args_exec(char **args_exec, int ret)
{
	int	i;

	i = 0;
	while (args_exec[i])
	{
		free(args_exec[i]);
		i++;
	}
	free(args_exec);
	return (ret);
}

int	ft_msg(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
	return (FAILURE);
}

int	msg_perror(char *origin)
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
