/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:02:36 by frrusso           #+#    #+#             */
/*   Updated: 2022/06/09 16:02:39 by frrusso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen_equal(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (i);
}

char	*ft_str_whitout_equal(char *envp)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	while (envp[i] && envp[i] != '=')
		i++;
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	j = 0;
	while (i)
	{
		res[j] = envp[j];
		i--;
		j++;
	}
	res[j] = '\0';
	return (res);
}

// Find the var to unset
int	ft_unset_str(char **line, char **envp, int i, int *k)
{
	char	*str;

	str = ft_str_whitout_equal(envp[i]);
	if (!str)
		return (2);
	if (ft_strncmp(str, line[1], ft_strlen(str)) == 0)
	{
		*k = 1;
		free(str);
		return (1);
	}
	free(str);
	return (0);
}

char	**ft_unset_free(int i, char **res)
{
	res[i] = NULL;
	return (ft_split_free(res));
}

char	**ft_unset_envp(char **line, char **envp)
{
	int		i;
	int		j;
	int		k;
	char	**res;

	res = malloc(sizeof(char *) * (ft_string_of_string_len(envp) - 1));
	if (!res)
		return (NULL);
	k = 0;
	i = -1;
	while (envp[++i])
	{
		j = ft_unset_str(line, envp, i, &k);
		if (j == 1)
			continue ;
		else if (j == 2)
			return (ft_unset_free(i - k, res));
		res[i - k] = malloc(sizeof(char) * (ft_strlen(envp[i]) + 1));
		if (!res[i - k])
			return (NULL);
		ft_memcpy(res[i - k], envp[i], ft_strlen(envp[i]) + 1);
	}
	res[i - k] = NULL;
	return (res);
}
