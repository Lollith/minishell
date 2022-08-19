/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:40:53 by frrusso           #+#    #+#             */
/*   Updated: 2022/08/19 08:47:04 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_no_file(char **line, char **bis, t_pipe *pipex)
{
	if (line[1] && line[1][0] && bis[1] != NULL)
	{
		printf("minishell: cd: %s: No such file or directory\n", line[1]);
		pipex->pipe_ret_b = 1;
	}
}

int	ft_cd_exec(char **line, char ***envp, char **bis, t_pipe *pipex)
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
	if (ret < 0 || bis[1] == NULL)
	{
		cd_no_file (line, bis, pipex);
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
