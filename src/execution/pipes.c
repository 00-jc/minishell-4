/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:29:39 by edblazqu          #+#    #+#             */
/*   Updated: 2026/01/18 13:34:29 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dup2_manager(t_redir *redir)
{
	t_redir	*current;
	
	if (!redir)
		return (1);
	current = redir;
	while (current)
	{
		printf("tipo: %d", current->type);
		if (current->type == T_INFILE)
		{
			if (dup2(current->fd, STDIN_FILENO) == -1)
				return (0);
		}
		else if (current->type == T_OUTFILE || current->type == T_APPEND)
		{
			if (dup2(current->fd, STDOUT_FILENO) == -1)
				return (0);			
		}
		close(current->fd);
		current = current->next;
	}
	return (1);
}

void	close_pipes(int pipe[2])
{
	close(pipe[0]);
	close(pipe[1]);
}
