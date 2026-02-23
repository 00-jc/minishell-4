/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 11:39:16 by edblazqu          #+#    #+#             */
/*   Updated: 2026/02/06 11:39:17 by edblazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipes(t_tree *node)
{
	int		count;

	count = 0;
	while (node && node->type == N_PIPE)
	{
		count++;
		node = node->right;
	}
	return (count);
}

static int	collect_cmd(t_tree *node, t_cmd ***cmds)
{
	int	n;
	int	i;

	n = count_pipes(node) + 1;
	*cmds = malloc(sizeof(t_cmd *) * n);
	if (!*cmds)
		return (0);
	i = 0;
	while (node->type == N_PIPE)
	{
		(*cmds)[i++] = node->left->cmd;
		node = node->right;
	}
	(*cmds)[i] = node->cmd;
	return (n);
}

static void	run_child(t_shell *shell, t_cmd *cmd, int in_fd, int out_fd)
{
	setup_signals_child();
	if (in_fd != -1)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != -1)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	if (!check_redirs(cmd) || !dup2_manager(cmd->redir))
		exit(126);
	if (is_builtin(cmd, shell->envp))
	{
		execute_builtin(shell, cmd, &shell->envp);
		exit(shell->program_exit);
	}
	cmd->execute = tokens_to_args(cmd->args);
	execve(search_cmd(cmd->execute[0], shell), cmd->execute, shell->envp);
	perror("minishell");
	exit(127);
}

static void	fork_all(t_shell *shell, t_cmd **cmds, pid_t *pids, int	n)
{
	int	fd[2];
	int	prev_fd;
	int	i;

	prev_fd = -1;
	i = 0;
	while (i < n)
	{
		if (i < n - 1)
			pipe(fd);
		else
		{
			fd[0] = -1;
			fd[1] = -1;
		}
		pids[i] = fork();
		if (pids[i] == 0)
			run_child(shell, cmds[i], prev_fd, fd[1]);
		if (prev_fd != -1)
			close(prev_fd);
		if (fd[1] != -1)
			close(fd[1]);
		prev_fd = fd[0];
		i++;
	}
}

int	execute_pipe(t_shell *shell, t_tree *node)
{
	t_cmd	**cmds;
	pid_t	*pids;
	int	status;
	int	n;
	int	i;

	n = collect_cmd(node, &cmds);
	if (!n)
		return (0);
	pids = malloc(sizeof(pid_t) * n);
	if (!pids)
		return (free(cmds), 0);
	setup_signals_running();
	fork_all(shell, cmds, pids, n),
	free(cmds);
	i = 0;
	while (i < n)
	{
		waitpid(pids[i], &status, 0);
		if (i == n - 1)
			shell->program_exit = WEXITSTATUS(status);
		i++;
	}
	return (free(pids), i);
}
