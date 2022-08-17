/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 10:15:29 by agouet            #+#    #+#             */
/*   Updated: 2022/08/17 17:48:30 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// > file => creer file
// > file ls  = ls > file
// ls > file1 > file2: creer les 2 files , ecrase f1 et f2 + \n fd file2
// echo test > file test1  = exho test test1 > file
// bad cmd > file  : crer file ms erreur cmd
// si file existe recup arg[1] sinon recup sur la liste chainee
// et le suprime de la liste
int	ft_redir_out(t_list *l_token, char **args_exec, char ***envp, t_pipe *pipex)
{
	int		fd;

	fd = open_out(l_token, args_exec);
	if (fd < 0)
		return (FAILURE);
	if (l_token->next)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (ft_msg_perror("dup2 "));
		close(fd);
	//while(l_token)
	//{
	//	printf("%s\n", (char*)l_token->content);
	//	l_token=l_token->next;
	//}
		if (monitoring(l_token, l_token->next, envp, pipex) == 0)
			return (FAILURE);
	}
	close(fd);
	return (SUCCESS);
}

// ligne si !file toujours utile??
int	open_out(t_list *l_token, char **args_exec)
{
	char	*file;
	int		fd;

	fd = 0;
	file = args_exec[1];
	if (!file)
	{
		file = l_token->next->content;
		ft_l_delete(l_token);
	}
	if (ft_strncmp(l_token->content, ">>", 2) == 0)
		fd = open (file, O_WRONLY | O_APPEND | O_CREAT, 0666);
	else
		fd = open (file, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fd < 0)
		perror(file);
	ft_split_free(args_exec);
	return (fd);
}

// bash : cmd1 < file1 < file2 => result file2, si 1 existe pas
// => erreur file1 c tout
// => < (-file1) cmd < (-file2)
// => < (-file1) < (-file2) cmd1
// cat << EOF => ]<<] [EOF]  + cat
int	ft_redir_in(t_list *l_token, char **args_exec, char ***envp, t_pipe *pipex)
{
	int		fd;
	char	*file;

	dup2(pipex->tmp_in, STDIN_FILENO);
	file = open_in(l_token, args_exec);
	if (!file)
		return (FAILURE);
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror(file);
		return (FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
		return (ft_msg_perror("dup2 "));
	if (close(fd) < 0)
		return (ft_msg_perror("fd "));
	if (ft_strncmp(l_token->content, "<<", 2) == 0)
		free_heredoc(file);
	ft_split_free(args_exec);
	if ((l_token)->next)
		monitoring(l_token, l_token->next, envp, pipex);
	return (SUCCESS);
}

char	*open_in(t_list *l_token, char **args_exec)
{
	char	*file;

	if (ft_strncmp(l_token->content, "<<", 2) == 0)
	{
		file = ft_heredoc(args_exec);
		if (!file)
		{
			ft_split_free(args_exec);
			return (NULL);
		}
	}
	else
		file = args_exec[1];
	return (file);
}

int	next_checker(t_list *l_token)
{
	while (l_token)
	{
		if (is_operator(l_token) && !l_token->next)
		{
			printf("syntax error near unexpected token\n");
			return (FAILURE);
		}
		l_token = l_token->next;
	}
	return (SUCCESS);
}
