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
	char	name[BUFFER_NAME];
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

int	minishell_len_quote_bis(char const *str, int i, int *j, char c)
{
	i++;
	while (str[i] != c)
	{
		i = minishell_env_var(str, i, j, 1);
		*j += 1;
	}
	return (i + 1);
}
