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
	ft_split_free(bis);
}

int	ft_cd_exec(char **line, char ***envp, char **bis, t_pipe *pipex)
{
	int		ret;
	char	*str;

	if (!ft_get_home(*envp, 1))
		pipex->pipe_ret_b = 1;
	if (!line[1] || ft_is_str(line[1], "~"))
		ret = chdir(ft_get_home(*envp, 0));
	else if (line[1][0] == '~')
	{
		str = ft_strjoin(ft_get_home(*envp, 0), line[1] + 1);
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
		cd_no_file(line, bis, pipex);
		return (1);
	}
	return (0);
}

int	ft_export_init(char **line, char ***envp, char **tmp)
{
	if (!line[1])
		ft_print_string_of_string(*envp);
	*tmp = line[1];
	return (0);
}

int	ft_unset_i(char **line, char ***envp)
{
	int	i;

	i = 0;
	while (envp[0][i] && \
	(ft_strncmp(envp[0][i], line[1], ft_strlen_equal(envp[0][i]))) != 0)
		i++;
	return (i);
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
