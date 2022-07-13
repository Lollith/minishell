/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 13:29:11 by agouet            #+#    #+#             */
/*   Updated: 2022/07/13 16:59:32 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*creat_h_file(void)
{
	char	*file_heredoc;

	file_heredoc = (char *) malloc(sizeof(char) * 12);
	ft_memcpy (file_heredoc, ".heredoc_00", 12);
	return (file_heredoc);
}

char	*check_here_file(void)
{
	char	*file_heredoc;
	int		fd_tmp_h;
	int		i;
	char	j;

	file_heredoc = creat_h_file();
	j = 'a';
	while (j <= 'z')
	{
		i = 'a';
		while (i <= 'z')
		{
			file_heredoc[9] = j;
			file_heredoc[10] = i ;
			fd_tmp_h = open(file_heredoc, O_WRONLY | O_EXCL | O_CREAT, 0666);
			if (fd_tmp_h >= 0)
			{
				close(fd_tmp_h);
				return (file_heredoc);
			}
			i++;
		}
		j++;
	}
	return (NULL);
}

char	*ft_heredoc(t_list *l_token, char **args_exec)
{
	char	*line;
	int		size_EOF;
	char	*file_h;
	int		fd_tmp_h;

	(void) l_token;
	file_h = init_hd(&fd_tmp_h);
	size_EOF = ft_strlen(args_exec[1]);
	line = " ";
	while (line)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		if ((ft_strlen(line) - size_EOF == 1)
			&& (ft_strncmp(line, args_exec[1], size_EOF) == 0))
		{
			if (close(fd_tmp_h) < 0)
				return (NULL);
			free(line);
			return (file_h);
		}
		write(fd_tmp_h, line, ft_strlen(line));
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
	fd_tmp_h = open (file_h, O_WRONLY | O_CREAT, 0666);
	if (fd_tmp_h < 0)
		return (NULL);
	*pt_fd = fd_tmp_h;
	return (file_h);
}

void	free_heredoc(char *file1)
{
	unlink(file1);
	free (file1);
}
