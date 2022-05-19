/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:14:21 by frrusso           #+#    #+#             */
/*   Updated: 2022/05/19 15:14:23 by frrusso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac)
{
	static char	*line;

	if (ac != 1)
		return (0);
	line = NULL;
	if (line)
	{
		free(line);
		line = NULL;
	}
	line = readline("test> ");
	if (line && *line)
		add_history (line);
	printf("%s\n", line);
	return (0);
}
