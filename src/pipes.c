/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 00:52:03 by asoria            #+#    #+#             */
/*   Updated: 2026/01/11 02:12:32 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	op_is_pipe(void)
{
	return (0);
}

void	check_if_pipe(char *op, int *prev_fd, int (*pipe_fd)[2])
{
	if (op && ft_strncmp(op, "|", 1) == 0)
	{
		close((*pipe_fd)[1]);
		*prev_fd = (*pipe_fd)[0];
	}
	else
		*prev_fd = -1;
}

void	setup_pipe_fds(t_cmd *cmd, int prev_fd, int pipe_fd[2])
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->operator && ft_strncmp(cmd->operator, "|", 1) == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
}
