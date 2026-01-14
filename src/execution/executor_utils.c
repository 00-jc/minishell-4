/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 11:47:40 by edblazqu          #+#    #+#             */
/*   Updated: 2026/01/14 11:47:41 by edblazqu         ###   ########.fr       */
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
		return (cmd);
	i = 0;
	while (shell->path[i] && cmd != NULL)
	{
		route = ft_strjoin(shell->path[i], cmd);
		if (access(route, X_OK) == 0)
			break ;
		free(route);
		route = NULL;
		i++;
	}
	return (route);
}

void	init_redir(t_redirect *redir)
{
	redir->fd[0] = 0;
	redir->fd[1] = 1;
	redir->heredoc = 0;
	redir->prev_fd = -1;
	redir->n_child = 1;
	redir->child = malloc(sizeof(pid_t) * redir->n_child);
	if (!redir->child)
	{
		perror("Error: ");
		return ;
	}
}
