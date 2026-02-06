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

static void	erase_heredoc(t_redir *redir)
{
	if (redir->heredoc_name != NULL)
	{
		unlink(redir->heredoc_name);
		free(redir->heredoc_name);
	}
}

int	dup2_manager(t_redir *redir)
{
	t_redir	*current;
	
	if (!redir)
		return (1);
	current = redir;
	while (current)
	{
		if (current->type == T_INFILE || current->type == T_HEREDOC)
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
		erase_heredoc(current);
		current = current->next;
	}
	return (1);
}
