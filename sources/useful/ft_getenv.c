/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:40:53 by frrusso           #+#    #+#             */
/*   Updated: 2022/08/03 14:40:55 by frrusso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd_exec(char **line, char ***envp, char **bis)
{
	int		ret;
	char	*str;

	if (!line[1] || ft_is_str(line[1], "~"))
		ret = chdir(ft_get_home(*envp));
	else if (line[1][0] == '~')
	{
		str = ft_strjoin(ft_get_home(*envp), line[1] + 1);
		if (!str)
			return (2);
		ret = chdir(str);
		free(str);
	}
	else if (ft_is_str(line[1], "-"))
		ret = chdir(ft_getenv("OLDPWD", *envp));
	else
		ret = chdir(line[1]);
	if (ret < 0)
	{
		if (line[1] && line[1][0])
			printf("minishell: cd: %s: No such file or directory\n", line[1]);
		ft_split_free(bis);
		return (1);
	}
	return (0);
}

char	*ft_getenv(char *env, char **envp)
{
	int	i;

	if (!env)
		return (NULL);
	i = 0;
	while (envp[i] && \
	(ft_strncmp(envp[i], env, ft_strlen_equal(envp[i])) != 0))
		i++;
	if (envp[i])
		return (envp[i] + ft_strlen(env) + 1);
	return (NULL);
}
