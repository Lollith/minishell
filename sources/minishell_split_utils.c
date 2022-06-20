/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:24:45 by frrusso           #+#    #+#             */
/*   Updated: 2022/06/20 15:24:48 by frrusso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_chrcpy(char const *str, char *res, int *i, int *j)
{
	res[*j] = str[*i];
	*i += 1;
	*j += 1;
}

int	minishell_env_post_input(char const *str, int i, int *input)
{
	int		var;
	char	name[128];
	char	*value;

	if (str[i] == '$')
	{
		i++;
		var = 0;
		while (ft_isalnum(str[i + var]))
			var++;
		ft_memcpy(name, str + i, var);
		name[var] = '\0';
		value = getenv(name);
		if (value)
			*input -= ft_strlen(value);
		return (i + var);
	}
	return (i);
}
