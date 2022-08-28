/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:40:53 by frrusso           #+#    #+#             */
/*   Updated: 2022/08/19 08:47:04 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *env, char **envp)
{
	int	i;

	if (!env)
		return (NULL);
	i = 0;
	while (envp[i] && \
	(ft_strncmp(envp[i], env, ft_strlen_equal(env)) != 0))
		i++;
	if (envp[i])
		return (envp[i] + ft_strlen(env) + 1);
	return (NULL);
}
