/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:11:16 by agouet            #+#    #+#             */
/*   Updated: 2022/07/13 16:14:45 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// si cmd < file1 => <file cmd => passe ds ft_isarg
// => tab de [0]"<" [1]"file" => < cat
// logiuement la cmd va se retourvee systematiquenet a ka fin
// cat < file1 < file2 => < file1 < file2 < cat
void	reorganize(t_list **l_token, char **args_exec)
{
	t_list	*tmp;
	int		i;
	t_list	*new;

	i = 1;
	if ((*l_token)->next
		&& ((ft_strncmp((*l_token)->next->content, "<", 1) == 0)
			|| (ft_strncmp((*l_token)->next->content, ">", 1) == 0)))
	{
		tmp = (*l_token)->next;
		(*l_token)->next = NULL;
		while (args_exec[i])
		{
			new = ft_lstnew (args_exec[i]);
			ft_lstlast(*l_token)->next = new;
			i++;
		}
		ft_lstlast(*l_token)->next = NULL;
		if (tmp->next->next)
			ft_lstadd_back(l_token, tmp->next->next);
		else
			ft_lstlast(*l_token)->next = NULL;
		tmp->next->next = (*l_token);
		(*l_token) = tmp;
	}
}

int	check_op(t_list *l_token, char **args_exec, char ***envp, t_pipe *pipex)
{
	char	**file_redir;

	reorganize(&l_token, args_exec);
	file_redir = ft_is_arg(l_token);
	if (ft_strncmp(l_token->next->content, "&&", 2) == 0)
		ft_eperluet(l_token, args_exec, envp, pipex);
	else if (ft_strncmp(l_token->next->content, "||", 2) == 0)
		ft_ou(l_token, args_exec, envp, pipex);
	else if (ft_strncmp(l_token->next->content, "|", 1) == 0)
		ft_pipex(l_token, args_exec, envp, pipex);
	else if (ft_strncmp(l_token->content, ">", 1) == 0)
		{
		if(ft_redir_out(l_token, file_redir, envp, pipex) ==0)
			return 0;
		}
	else if (ft_strncmp(l_token->content, "<", 1) == 0)
		ft_redir_in(l_token, file_redir, envp, pipex);
	return 1;
}

int	monitoring_line(t_list *l_token, char ***envp, t_pipe *pipex)
{
	char	**args_exec;

	args_exec = ft_is_arg(l_token);
	if (l_token->next)
		{
			if (check_op(l_token, args_exec, envp, pipex) == 0)
				return 1;
		}
	else
	{
		if (ft_strncmp(l_token->content, ">", 1) == 0)
			ft_redir_out(l_token, args_exec, envp, pipex);
		else
		{
			pipex->ctrl = -1;
			if (ft_child(&args_exec, envp, l_token, pipex) == 1)
				exit (1);
		}
	}
	pipex->ctrl = 0;
	return (ft_free_args_exec(args_exec, FAILURE));
}
