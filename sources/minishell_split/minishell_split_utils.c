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

// int	minishell_env_res(char *res, char const *str, int i, int *j)
// {
// 	int		k;
// 	int		var;
// 	char	name[BUFFER_NAME];
// 	char	*value;

// 	i++;
// 	var = 0;
// 	while (ft_isalnum(str[i + var]))
// 		var++;
// 	ft_memcpy(name, str + i, var);
// 	name[var] = '\0';
// 	value = getenv(name);
// 	if (value)
// 	{
// 		k = 0;
// 		while (value[k])
// 		{
// 			res[*j] = value[k];
// 			k++;
// 			*j += 1;
// 		}
// 	}
// 	return (i + var);
// }

// int	minishell_env_var(char const *str, int i, int *j, int pp)
// {
// 	int		var;
// 	char	name[BUFFER_NAME];
// 	char	*value;

// 	if (str[i] == '$')
// 	{
// 		i++;
// 		var = 0;
// 		while (ft_isalnum(str[i + var]))
// 			var++;
// 		ft_memcpy(name, str + i, var);
// 		name[var] = '\0';
// 		value = getenv(name);
// 		if (value)
// 			*j += ft_strlen(value);
// 		return (i + var);
// 	}
// 	return (i + pp);
// }

// int	minishell_env_post_input(char const *str, int i, int *input)
// {
// 	int		var;
// 	char	name[BUFFER_NAME];
// 	char	*value;

// 	if (str[i] == '$')
// 	{
// 		i++;
// 		var = 0;
// 		while (ft_isalnum(str[i + var]))
// 			var++;
// 		ft_memcpy(name, str + i, var);
// 		name[var] = '\0';
// 		value = getenv(name);
// 		if (value)
// 			*input -= ft_strlen(value);
// 		return (i + var);
// 	}
// 	return (i);
// }
