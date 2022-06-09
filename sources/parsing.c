/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 10:08:20 by agouet            #+#    #+#             */
/*   Updated: 2022/05/25 10:16:57 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_quote(char *line)
{
	int	i;
	int	two;
	int	one;

	if (!line)
		return (FALSE);
	two = 0;
	one = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\"')
			two++;
		if (line[i] == '\'')
			one++;
		i++;
	}
	if (two % 2 == 1 || one % 2 == 1)
		return (FALSE);
	return (TRUE);
}

// fonction qui cree les "mots" en fonction des espaces
// token est free dans minishell par ft_free_split
char	**lexer(char *line)
{
	char	**token;

	if (!ft_quote(line))
		return (NULL);
	token = minishell_split(line, " \t\n\v\f\r");
	if (!token)
		return (NULL);
	return (token);
}
