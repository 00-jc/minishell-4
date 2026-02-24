/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 22:09:11 by edblazqu          #+#    #+#             */
/*   Updated: 2026/02/24 22:09:11 by edblazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dup_std(int std_fd[2])
{
	std_fd [0] = dup(STDOUT_FILENO);
	std_fd [1] = dup(STDIN_FILENO);
	if (std_fd[0] == -1 || std_fd[1] == -1)
		return (0);
	return (1);
}

int	redir_builtin(t_cmd *cmd, int std_fd[2])
{
	t_redir	*current;
	int		control;

	if (!cmd->redir || !dup_std(std_fd))
		return (1);
	current = cmd->redir;
	while (current)
	{
		control = 1;
		if (current->type == T_INFILE)
			control = redir_infile(current);
		else if (current->type == T_OUTFILE)
			control = redir_outfile(current);
		else if (current->type == T_APPEND)
			control = redir_append(current);
		else if (current->type == T_HEREDOC)
			control = redir_heredoc(current);
		if (!control)
			return (0);
		current = current->next;
	}
	return (1);
}

int	std_builtin(t_cmd *cmd, int std_fd[2])
{
	if (!cmd->redir)
		return (1);
	if (dup2(std_fd[0], STDOUT_FILENO) == -1)
		return (0);
	if (dup2(std_fd[1], STDIN_FILENO) == -1)
		return (0);
	close(std_fd[0]);
	close(std_fd[1]);
	return (1);
}
