/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 00:52:03 by asoria            #+#    #+#             */
/*   Updated: 2026/01/06 02:41:48 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	op_is_pipe(void)
{
	return (0);
}

void	execute_pipeline(t_shell *shell)
{
	int		pipe_fd[2];
	int		prev_fd;
	pid_t	pids[(MAX_TOKENS / 2) + 1];
	int		i;
	int		cmd_count;
	t_cmd	*cmd;

	if (!shell->cmd_list)
		return ;
	cmd_count = count_commands(shell->cmd_list);
	cmd = shell->cmd_list;
	prev_fd = -1;
	i = 0;
	while (cmd)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("fork");
			if (prev_fd != -1)
				close(prev_fd);
			if (cmd->operator && ft_strncmp(cmd->operator, "|", 1) == 0)
			{
				close(pipe_fd[0]);
				close(pipe_fd[1]);
			}
			return ;
		}
		if (pids[i] == 0)
		{
			setup_pipe_fds(cmd, prev_fd, pipe_fd);
			execute_command(cmd, shell->envp);
		}
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->operator && ft_strncmp(cmd->operator, "|", 1) == 0)
		{
			close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
		}
		else
			prev_fd = -1;
		cmd = cmd->next;
		i++;
	}
	i = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
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
