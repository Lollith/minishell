/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 13:21:57 by frrusso           #+#    #+#             */
/*   Updated: 2022/08/25 13:22:00 by frrusso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd_no_file(char **line, char **bis, t_pipe *pipex)
{
	if (line[1] && line[1][0] && bis[1] != NULL)
	{
		printf("minishell: cd: %s: No such file or directory\n", line[1]);
		pipex->pipe_ret_b = 1;
	}
	ft_split_free(bis);
	return (1);
}

char	*ft_cd_get_home(char **envp, int is_cd)
{
	int		i;
	char	*home;

	home = NULL;
	i = 0;
	while (envp[i] && (ft_strncmp(envp[i], "HOME", 4) != 0))
		i++;
	if (envp[i])
		home = envp[i] + 5;
	else if (is_cd)
		ft_putstr_fd("minishell: cd: HOME not set\n", 1);
	return (home);
}

int	ft_cd_exec(char **line, char ***envp, char **bis, t_pipe *pipex)
{
	int		ret;
	char	*str;

	pipex->pipe_ret_b = 0;
	if (ft_cd_get_home(*envp, 1) == NULL)
		pipex->pipe_ret_b = 1;
	if (!line[1] || ft_is_str(line[1], "~"))
		ret = chdir(ft_cd_get_home(*envp, 0));
	else if (line[1][0] == '~')
	{
		str = ft_strjoin(ft_cd_get_home(*envp, 0), line[1] + 1);
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
		return (ft_cd_no_file(line, bis, pipex));
	return (0);
}

char	**ft_cd_export_line(char *pwd, char *line)
{
	char	cwd[256];
	char	**res;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		printf("minishell: cd: %s: No such file or directory\n", line);
		cwd[0] = '\0';
	}
	res = malloc(sizeof(char *) * 3);
	if (!res)
		return (NULL);
	res[0] = ft_strdup("export");
	if (!res[0])
		return (NULL);
	if (cwd[0])
	{
		res[1] = ft_strjoin(pwd, cwd);
		if (!res[1])
			return (NULL);
	}
	else
		res[1] = NULL;
	res[2] = NULL;
	return (res);
}

int	ft_cd(char **line, char ***envp, t_pipe *pipex)
{
	int		i;
	char	**bis;

	if (ft_string_of_string_len(line) >= 4)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 1);
		pipex->pipe_ret_b = 1;
		return (1);
	}
	bis = ft_cd_export_line("OLDPWD=", line[1]);
	if (!bis)
		return (2);
	i = ft_cd_exec(line, envp, bis, pipex);
	if (i > 0)
		return (i);
	if (ft_export(bis, envp, pipex) == 2)
		return (2);
	ft_split_free(bis);
	bis = ft_cd_export_line("PWD=", NULL);
	if (!bis || ft_export(bis, envp, pipex) == 2)
		return (2);
	ft_split_free(bis);
	pipex->pipe_ret = 0;
	return (1);
}
