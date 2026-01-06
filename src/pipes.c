/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 00:52:03 by asoria            #+#    #+#             */
/*   Updated: 2026/01/06 03:23:05 by asoria           ###   ########.fr       */
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

void	execute_pipeline(t_shell *shell)
{
	int		prev_fd;
	int		pipe_fd[2];
	t_cmd	*cmd;

	if (!shell->cmd_list)
		return ;
	prev_fd = -1;
	cmd = shell->cmd_list;
	while (cmd)
	{
		if (cmd->operator && ft_strncmp(cmd->operator, "|", 1) == 0)
			pipe(pipe_fd);
		if (fork() == 0)
		{
			setup_pipe_fds(cmd, prev_fd, pipe_fd);
			execute_command(cmd, shell->envp);
		}
		if (prev_fd != -1)
			close(prev_fd);
		check_if_pipe(cmd->operator, &prev_fd, &pipe_fd);
		cmd = cmd->next;
	}
	while (wait(NULL) > 0)
		;
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
