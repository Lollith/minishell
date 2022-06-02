/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:14:21 by frrusso           #+#    #+#             */
/*   Updated: 2022/06/02 11:48:13 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_msg(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
	return (FAILURE);
}

int	msg_perror(char *origin)
{
	perror(origin);
	exit(FAILURE);
}

void	ft_new_prompt(int signum)
{
	if (signum == SIGINT)
	{
		ft_msg("\b\b  \n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
		ft_msg("\b\b  \b\b", 1);
}

int	check_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (ft_msg("Error: path not found\n", 2));
	return (SUCCESS);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_list	*l_token;
	t_list	*tmp_token;

	l_token = NULL;
	(void)av;
	if (!check_env(envp))
		return (1);
	if (ac != 1)
		return (ft_msg("Usage : ./minishell\n", 1));
	signal(SIGINT, ft_new_prompt);
	signal(SIGQUIT, ft_new_prompt);
	line = readline("minishell> ");
	while (line != NULL)
	{
		add_history (line);
	//	ac = minishell(line, envp);
		if (!list_token(&l_token, line))
			return (1);
		tmp_token = l_token;
		monitoring_line(tmp_token, envp);
		ft_lstclear2(&l_token);
		free(line);
		if (ac == 2)
			break ;
		line = readline("minishell> ");
	}
	rl_clear_history();
	return (ft_msg("\n", 1));
}
