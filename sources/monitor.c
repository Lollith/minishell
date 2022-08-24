/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:11:16 by agouet            #+#    #+#             */
/*   Updated: 2022/08/24 10:33:20 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// si cmd < file1 => <file cmd => passe ds ft_isarg
// => tab de [0]"<" [1]"file" => < cat
// logiuement la cmd va se retourvee systematiquenet a ka fin
// cat < file1 < file2 => < file1 < file2 < cat
// regorga en tenant compte des flags et file des arg_exec
int	reorga(t_list **l_token, char **exec, char ***fil_redir, t_pipe *pipex)
{
	t_list	*tmp;
	int		i;
	t_list	*new;

	i = 1;
	if ((*l_token)->next && (ft_strncmp((*l_token)->content, "<", 1) != 0) && \
	((ft_strncmp((*l_token)->next->content, "<", 1) == 0) || \
	(ft_strncmp((*l_token)->next->content, ">", 1) == 0)))
	{
		tmp = (*l_token)->next;
		(*l_token)->next = NULL;
		while (exec[i])
		{
			new = ft_lstnew (strdup(exec[i]));
			ft_lstlast(*l_token)->next = new;
			i++;
		}
		reorga2(l_token, tmp);
		*fil_redir = ft_is_arg(*l_token);
		split_free_null(exec);
		pipex->l_start = *l_token;
		return (SUCCESS);
	}
	*fil_redir = exec;
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

int	check_op(t_list *l_token, char **exec, char ***envp, t_pipe *pipex)
{
	int		i;
	char	**file_redir;

	i = 1;
	pipex->ctrl_redir = 0;
	if (reorga(&l_token, exec, &file_redir, pipex) == 1)
		pipex->ctrl_redir = 1;
	if (ft_strncmp(l_token->next->content, "&&", 2) == 0)
		ft_eperluet(l_token, exec, envp, pipex);
	else if (ft_strncmp(l_token->next->content, "||", 2) == 0)
		ft_ou(l_token, exec, envp, pipex);
	else if (ft_strncmp(l_token->next->content, "|", 1) == 0)
		i = ft_pipex(l_token, exec, envp, pipex);
	else if (ft_strncmp(l_token->content, ">", 1) == 0)
		i = ft_redir_out(l_token, file_redir, envp, pipex);
	else if (ft_strncmp(l_token->content, "<", 1) == 0)
		i = ft_redir_in(l_token, file_redir, envp, pipex);
	if (i == 0)
		return (FAILURE);
	return (SUCCESS);
}

int	monitoring(t_list *start, t_list *l_token, char ***envp, t_pipe *pipex)
{
	char	**args_exec;

	ft_clean_redir(pipex);
	args_exec = ft_is_arg(l_token);
	if (args_exec == NULL)
		return (FAILURE);
	pipex->l_start = start;
	if (l_token->next)
	{
		if (check_op(l_token, args_exec, envp, pipex) == 0)
			return (FAILURE);
	}
	else
		if (one_cmd(l_token, args_exec, envp, pipex) == 0)
			return (FAILURE);
	return (SUCCESS);
}

int	one_cmd(t_list *l_token, char **args_exec, char ***envp, t_pipe *pipex)
{
	if (ft_strncmp(l_token->content, ">", 1) == 0)
	{
		if (ft_redir_out(l_token, args_exec, envp, pipex) == 0)
			return (FAILURE);
	}
	else
	{
		pipex->ctrl = -1;
		ft_child(&args_exec, envp, l_token, pipex);
		pipex->nb_pipes = 0;
	}
	return (SUCCESS);
}
