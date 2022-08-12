/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 15:01:18 by agouet            #+#    #+#             */
/*   Updated: 2022/08/12 15:25:54 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_heredoc(char *file1)
{
	unlink(file1);
	free(file1);
}

char	*creat_h_file(void)
{
	char	*file_heredoc;

	file_heredoc = malloc(sizeof(char) * 12);
	if (!file_heredoc)
		return (FAILURE);
	ft_memcpy(file_heredoc, ".heredoc_00", 12);
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
