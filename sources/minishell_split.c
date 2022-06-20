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
	printf("connt=%i\n", res);
	return (res);
}

int	minishell_len(char const *str, char *space, int i)
{
	int	j;

	j = 1;
	while (str[i])
	{
		i = minishell_len_quote(str, i, &j);
		if (ft_is_space(str[i], space))
		{
			printf("len=%i\n", j);
			return (j);
		}
	}
	printf("len=%i\n", j);
	return (j);
}

char	*minishell_input(char const *str, char *space, int i)
{
	int		j;
	int		k;
	int		len;
	char	*res;

	len = minishell_len(str, space, i);
	res = malloc(sizeof(char) * len);
	if (!res)
		return (NULL);
	j = 0;
	while (--len && str[i])
	{
		while (ft_is_space(str[i], "\"\'"))
			i++;
		if (str[i] == '$')
		{
			k = j;
			i = minishell_env_res(res, str, i, &j);
			len = j - k - 1;
			continue ;
		}
		ft_chrcpy(str, res, &i, &j);
	}
	res[j] = '\0';
	return (res);
}

int	minishell_post_input(char const *str, char *space, int i, char *res)
{
	int	k;
	int	input;

	input = ft_strlen(res);
	while (input)
	{
		k = i;
		i = minishell_env_post_input(str, i, &input);
		if (!str[i])
			break ;
		if (k != i)
			continue ;
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

// 05 - 9 8 4 4
// 03 - 7 11
// 10 - 5 3 2 1 2 1 2 1 2
// 03 - 5 8
// 04 - 5 1 4
// 10 - 6 2 2 3 2 2 3 4 5
// int	main(void)
// {
// 	char	**token;

// 	token = minishell_split("\"Bonjour|\" Bonsoir les ami", " \t\n\v\f\r");
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

// 03 - 8 8
// 02 - 5
// 02 - 1
// 02 - 2
// 02 - 6
// 03 - 9 8 
int	main(void)
{
	char	**token;

	token = minishell_split("Bonjour $USER", " \t\n\v\f\r");
	ft_print_string_of_string(token);
	ft_split_free(token);
	printf("---------------------------------------------------------------\n");
	token = minishell_split("$TEST", " \t\n\v\f\r");
	ft_print_string_of_string(token);
	ft_split_free(token);
	printf("---------------------------------------------------------------\n");
	token = minishell_split("\"$TEST0\"", " \t\n\v\f\r");
	ft_print_string_of_string(token);
	ft_split_free(token);
	printf("---------------------------------------------------------------\n");
	token = minishell_split("\'$TEST1\'", " \t\n\v\f\r");
	ft_print_string_of_string(token);
	ft_split_free(token);
	printf("---------------------------------------------------------------\n");
	token = minishell_split("$TEST2$TEST3", " \t\n\v\f\r");
	ft_print_string_of_string(token);
	ft_split_free(token);
	printf("---------------------------------------------------------------\n");
	token = minishell_split("Aurevoir $LOGNAME", " \t\n\v\f\r");
	ft_print_string_of_string(token);
	ft_split_free(token);
}
