/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:44:51 by frrusso           #+#    #+#             */
/*   Updated: 2022/06/02 14:10:47 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_list *l_token)
{

//	if (ft_is_str(l_token->next->content, "-n"))
//		l_token = l_token->next;
	while (l_token->next)
	{
		printf("%s",(char *) l_token->next->content);
		l_token = l_token->next;
	}
	//if (!ft_is_str(l_token->next->content, "-n"))
		printf("\n");
	return (1);
}

char	*get_home(char **envp)
{
	int		i;
	char	*home;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "HOME=", 5))
		i++;
	home = envp[i] + 5;
	return (home);
}

int	ft_cd(char **line, char **envp)
{
	char	*home;

	home = get_home(envp);
	if (line[1])
		chdir(line[1]);
	else
		chdir(home);
	return (1);
}

int	ft_pwd(void)
{
	char	cwd[256];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd() error");
	else
		printf("%s\n", cwd);
	return (1);
}
