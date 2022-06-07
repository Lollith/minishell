/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:07:18 by frrusso           #+#    #+#             */
/*   Updated: 2022/05/25 12:07:31 by frrusso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_count(char const *str, char *space)
{
	int	i;
	int	j;
	int	res;

	i = 0;
	j = ft_is_space(str[i], space);
	res = 1;
	while (str[i])
	{
		i = minishell_quote(str, i);
		if (!j && ft_is_space(str[i], space))
		{
			j = TRUE;
			res++;
		}
		if (j && !ft_is_space(str[i], space))
			j = FALSE;
		i++;
	}
	printf("[count=%i]\n", res);
	return (res);
}

int	minishell_len(char const *str, char *space, int i)
{
	int	j;
	int	tmp;

	j = 1;
	while (str[i])
	{
		tmp = minishell_quote(str, i);
		j += tmp - i;
		i = tmp;
		if (ft_is_space(str[i], space))
		{
			printf("[len=%i]", j);
			return (j);
		}
		i++;
		j++;
	}
	printf("[len=%i]", j);
	return (j);
}

char	*minishell_input(char const *str, char *space, int i)
{
	int		j;
	int		len;
	char	*res;

	len = minishell_len(str, space, i);
	res = malloc(sizeof(char) * len);
	if (!res)
		return (NULL);
	j = 0;
	while (--len)
	{
		res[j] = str[i];
		i++;
		j++;
	}
	res[j] = '\0';
	printf("[input=%s]\n", res);
	return (res);
}

int	minishell_post_input(char const *str, char *space, int i, char *res)
{
	i += ft_strlen(res);
	while (str[i] && !ft_is_space(str[i], space))
		i++;
	return (i);
}

char	**minishell_split(char const *str, char *space)
{
	int		i;
	int		j;
	char	**res;

	res = malloc(sizeof(char *) * minishell_count(str, space));
	if (!res)
		return (NULL);
	j = 0;
	i = 0;
	while (str[i])
	{
		while (ft_is_space(str[i], space))
			i++;
		if (str[i])
			res[j] = minishell_input(str, space, i);
		else
			break ;
		if (!res[j])
			return (ft_split_free(res));
		i = minishell_post_input(str, space, i, res[j]);
		j++;
	}
	res[j] = NULL;
	return (res);
}

// int	main(void)
// {
// 	char	**token;

// 	token = minishell_split("Bonjour \" Bonsoir\\n \" ", " \t\n\v\f\r");
// 	ft_print_string_of_string(token);
// 	token = minishell_split(" \" Bonsoir\\n \" Bonjour les ami", " \t\n\v\f\r");
// 	ft_print_string_of_string(token);
// 	return (0);
// }
