
  
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

// fonction qui cree les "mots" en fonction des espaces
// token est free dans minishell par ft_free_split
// a modifier => gerer les ; "" ''
// a modifier => gerer tous les espaces " \t\n\v\f\r"
char	**lexer(char *line)
{
	char	**token;

	token = ft_split(line, ' ');
	if (!token)
		return (NULL);
	return (token);
}

