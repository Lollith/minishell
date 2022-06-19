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
	res = 2;
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
	return (res);
}

int	minishell_len(char const *str, char *space, int i)
{
	int	j;

	j = 1;
	while (str[i])
	{
		i = minishell_len_quote(str, i, &j);
		if (ft_is_space(str[i], space) || !str[i])
			return (j);
		i++;
		j++;
	}
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
		while (ft_is_space(str[i], "\"\'"))
			i++;
		if (str[i] == '$')
		{
			i = minishell_env_res(res, str, i, &j);
			continue ;
		}
		res[j] = str[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}

int	minishell_post_input(char const *str, char *space, int i, char *res)
{
	int	input;

	input = ft_strlen(res);
	while (input)
	{
		if (!ft_is_space(str[i], "\"\'"))
			input--;
		i++;
	}
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

// 	token = minishell_split("Bonjour", " \t\n\v\f\r");
// 	ft_print_string_of_string(token);
// 	ft_split_free(token);
// 	printf("---------------------------------------------------------------\n");
// 	token = minishell_split("$TEST", " \t\n\v\f\r");
// 	ft_print_string_of_string(token);
// 	ft_split_free(token);
// 	printf("---------------------------------------------------------------\n");
// 	token = minishell_split("\"$TEST1\"", " \t\n\v\f\r");
// 	ft_print_string_of_string(token);
// 	ft_split_free(token);
// 	printf("---------------------------------------------------------------\n");
// 	token = minishell_split("\'$TEST0\'", " \t\n\v\f\r");
// 	ft_print_string_of_string(token);
// 	ft_split_free(token);
// 	printf("---------------------------------------------------------------\n");
// 	token = minishell_split("$TEST3$TEST2", " \t\n\v\f\r");
// 	ft_print_string_of_string(token);
// 	ft_split_free(token);
// 	printf("---------------------------------------------------------------\n");
// 	token = minishell_split("Bonsoir", " \t\n\v\f\r");
// 	ft_print_string_of_string(token);
// 	ft_split_free(token);
// }

// int	main(void)
// {
// 	char	**token;

// 	token = minishell_split("\" Bonjour \" Bonjour les ami", " \t\n\v\f\r");
// 	ft_print_string_of_string(token);
// 	ft_split_free(token);
// 	printf("---------------------------------------------------------------\n");
// 	token = minishell_split("export A=\" coucou \"", " \t\n\v\f\r");
// 	ft_print_string_of_string(token);
// 	ft_split_free(token);
// 	printf("---------------------------------------------------------------\n");
// 	token = minishell_split("echo -n a '' b '' c '' d", " \t\n\v\f\r");
// 	ft_print_string_of_string(token);
// 	ft_split_free(token);
// 	printf("---------------------------------------------------------------\n");
// 	token = minishell_split("e\"ch\"o bonjour", " \t\n\v\f\r");
// 	ft_print_string_of_string(token);
// 	ft_split_free(token);
// 	printf("---------------------------------------------------------------\n");
// 	token = minishell_split("echo \"$ejnzefc\" hey", " \t\n\v\f\r");
// 	ft_print_string_of_string(token);
// 	ft_split_free(token);
// 	printf("---------------------------------------------------------------\n");
// 	token = minishell_split("mkdir a | cd a | rm -rf ../a", " \t\n\v\f\r");
// 	ft_print_string_of_string(token);
// 	ft_split_free(token);
// }
