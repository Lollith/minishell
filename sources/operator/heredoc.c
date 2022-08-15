/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:21:38 by agouet            #+#    #+#             */
/*   Updated: 2022/08/15 12:33:07 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ctrl d=> caractere non printable => gnl => return Null=> si ! line = ctrl+d
int	ctrld_heredoc(char **args_exec, char *line, int fd_tmp_h)
{
	if (!line && g_sig == 0)
	{
		write(1, "Warning: here-document delimited by end-of-file ", 49);
		write(1, "(wanted: ", 9);
		write(1, args_exec[1], ft_strlen(args_exec[1]));
		write(1, ")\n", 2);
		if (close(fd_tmp_h) < 0)
			return (FAILURE);
		free(line);
		return (SUCCESS);
	}
	return (FAILURE);
}

int	ctrlc_heredoc(int fd_tmp_h, char *file_h)
{
	if (g_sig == 1)
	{
		g_sig = 0;
		if (close(fd_tmp_h) < 0)
			return (FAILURE);
		free_heredoc(file_h);
		return (SUCCESS);
	}
	return (FAILURE);
}

int	heredoc_eof(char *line, char **args_exec, int fd_tmp_h)
{
	int		size_eof;

	size_eof = ft_strlen(args_exec[1]);
	if ((ft_strlen(line) - size_eof == 0)
		&& (ft_strncmp(line, args_exec[1], size_eof) == 0))
	{
		if (close(fd_tmp_h) < 0)
			return (FAILURE);
		return (SUCCESS);
	}
	return (FAILURE);
}

char	*ft_heredoc(char **args_exec)
{
	char	*line;
	char	*file_h;
	int		fd_tmp_h;

	fd_tmp_h = -1 ;
	signal(SIGINT, signal_here_doc);
	file_h = init_hd(&fd_tmp_h);
	line = " ";
	while (line != NULL)
	{
		line = readline("heredoc> ");
		if (ctrlc_heredoc(fd_tmp_h, file_h))
			return (NULL);
		if (heredoc_eof(line, args_exec, fd_tmp_h) == 1)
		{
			free(line);
			return (file_h);
		}
		if (ctrld_heredoc(args_exec, line, fd_tmp_h))
			return (file_h);
		write(fd_tmp_h, line, ft_strlen(line));
		write(fd_tmp_h, "\n", 1);
		free(line);
	}
	return (NULL);
}

char	*init_hd(int *pt_fd)
{
	char	*file_h;
	int		fd_tmp_h;

	fd_tmp_h = *pt_fd;
	file_h = check_here_file();
	fd_tmp_h = open(file_h, O_WRONLY | O_TRUNC, 0666);
	if (fd_tmp_h < 0)
		return (NULL);
	*pt_fd = fd_tmp_h;
	return (file_h);
}
