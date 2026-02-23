/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 11:47:40 by edblazqu          #+#    #+#             */
/*   Updated: 2026/01/18 23:04:44 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_cmd(char *cmd, t_shell *shell)
{
	char	*route;
	size_t	i;

	if (!cmd)
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	if (!shell ||!shell->path)
		return (NULL);
	i = 0;
	while (shell->path[i])
	{
		route = ft_strjoin(shell->path[i], cmd);
		if (access(route, X_OK) == 0)
			return (route);
		free(route);
		route = NULL;
		i++;
	}
	return (NULL);
}
