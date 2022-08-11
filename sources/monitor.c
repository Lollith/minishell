/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:11:16 by agouet            #+#    #+#             */
/*   Updated: 2022/08/11 15:21:43 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// si cmd < file1 => <file cmd => passe ds ft_isarg
// => tab de [0]"<" [1]"file" => < cat
// logiuement la cmd va se retourvee systematiquenet a ka fin
// cat < file1 < file2 => < file1 < file2 < cat
// regorga en tenant compte des flags et file des arg_exec
int	reorga(t_list **l_token, char **args_exec, char ***fil_redir, t_pipe *pipex)
{
	t_list	*tmp;
	int		i;
	t_list	*new;

	i = 1;
	if ((*l_token)->next && \
	((ft_strncmp((*l_token)->next->content, "<", 1) == 0) || \
	(ft_strncmp((*l_token)->next->content, ">", 1) == 0)))
	{
		tmp = (*l_token)->next;
		(*l_token)->next = NULL;
		while (args_exec[i])
		{
			new = ft_lstnew (strdup(args_exec[i]));
			ft_lstlast(*l_token)->next = new;
			i++;
		}
		reorga2(l_token, tmp);
		*fil_redir = ft_is_arg(*l_token);
		ft_split_free(args_exec);
		pipex->l_start = *l_token;
		return (SUCCESS);
	}
	*fil_redir = args_exec;
	return (FAILURE);
}

void	reorga2(t_list **l_token, t_list *tmp)
{
	ft_lstlast(*l_token)->next = NULL;
	if (tmp->next->next)
		ft_lstadd_back(l_token, tmp->next->next);
	else
		ft_lstlast(*l_token)->next = NULL;
	tmp->next->next = (*l_token);
	(*l_token) = tmp;
}

void	free_content(t_pipe *pipex)
{
	free(pipex->l_start->content);
	free(pipex->l_start);
}

int	check_op(t_list *l_token, char **args_exec, char ***envp, t_pipe *pipex)
{
	char	**file_redir;
	int		ctrl;

	ctrl = 0;
	if (reorga(&l_token, args_exec, &file_redir, pipex) == 1)
		ctrl = 1;
	if (ft_strncmp(l_token->next->content, "&&", 2) == 0)
		ft_eperluet(l_token, args_exec, envp, pipex);
	else if (ft_strncmp(l_token->next->content, "||", 2) == 0)
		ft_ou(l_token, args_exec, envp, pipex);
	else if (ft_strncmp(l_token->next->content, "|", 1) == 0)
	{
		if (ft_pipex(l_token, args_exec, envp, pipex) == 0)
			return (FAILURE);
	}
	else if (ft_strncmp(l_token->content, ">", 1) == 0)
	{
		if (ft_redir_out(l_token, file_redir, envp, pipex) == 0)
			return (FAILURE);
	}
	else if (ft_strncmp(l_token->content, "<", 1) == 0)
	{
		if (ft_redir_in(l_token, file_redir, envp, pipex) == 0)
			return (FAILURE);
	}
	if (pipex->l_start && ctrl == 1)
		free_content(pipex);
	return (SUCCESS);
}

int	monitoring_line(t_list *start, t_list *l_token, char ***envp, t_pipe *pipex)
{
	char	**args_exec;

	args_exec = ft_is_arg(l_token);
	pipex->l_start = start;
	if (args_exec == NULL)
		return (FAILURE);
	if (l_token->next)
	{
		if (check_op(l_token, args_exec, envp, pipex) == 0)
			return (FAILURE);
	}
	else
		one_cmd(l_token, args_exec, envp, pipex);
	pipex->ctrl = 0;
	return (SUCCESS);
}

int	one_cmd(t_list *l_token, char **args_exec, char ***envp, t_pipe *pipex)
{
	if (ft_strncmp(l_token->content, ">", 1) == 0)
	{
		if (ft_redir_out(l_token, args_exec, envp, pipex) == 0)
		{
			ft_split_free(args_exec);
			return (FAILURE);
		}
	}
	else
	{
		pipex->ctrl = -1;
		ft_child(&args_exec, envp, l_token, pipex);
		ft_split_free(args_exec);
	}
	return (SUCCESS);
}
