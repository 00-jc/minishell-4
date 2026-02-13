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

int	count_pipes(t_tree *root)
{
	t_tree	*node;
	int		count;

	if (!root || root->type != N_PIPE)
		return (0);
	node = root;
	count = 0;
	while (node)
	{
		if (node->type == N_PIPE)
			count++;
		node = node->right;
	}
	return (count);
}

void	close_pipes(int fd_pipe[2])
{
	close(fd_pipe[0]);
	close(fd_pipe[1]);
}

void	manage_pipe(t_pipe *info, int i)
{
	if (i == 0)
		dup2(info->pipe_fd[1], STDOUT_FILENO);
	else if (i == info->n_pipes)
		dup2(info->prev_fd, STDIN_FILENO);
	else
	{
		dup2(info->pipe_fd[1], STDOUT_FILENO);
		dup2(info->prev_fd, STDIN_FILENO);
	}
	if (i != 0)
		close(info->prev_fd);
	if (i != info->n_pipes)
		close_pipes(info->pipe_fd);
}

static void	new_child(t_shell *shell, t_tree *node, t_pipe *info, int i)
{
	t_cmd	*cmd;

	cmd = node->cmd;
	info->childs[i] = fork();
	if (info->childs[i] == 0)
	{
		manage_pipe(info, i);
		if (!check_redirs(cmd) || !dup2_manager(cmd->redir))
		{
			perror("minishell");
			exit (126);
		}
		if (is_builtin(cmd, shell->envp))
		{
			execute_builtin(shell, cmd, &shell->envp);
			exit (0);
		}
		cmd->execute = tokens_to_args(cmd->args, 0, count_tokens(cmd->args));
		execve(search_cmd(cmd->execute[0], shell), cmd->execute, shell->envp);
		perror("minishell");
		exit (127);
	}
}

int	execute_pipe(t_shell *shell, t_tree *node)
{
	t_pipe	info;
	int		i;

	info.n_pipes = count_pipes(node);
	info.childs = malloc(sizeof(pid_t) * (info.n_pipes + 1));
	if (!info.childs)
		return (0);
	info.prev_fd = -1;
	i = 0;
	while (node->type == N_PIPE)
	{
		pipe(info.pipe_fd);
		new_child(shell, node->left, &info, i);
		close(info.prev_fd);
		info.prev_fd = info.pipe_fd[0];
		close(info.pipe_fd[1]);
		node = node->right;
		i++;
	}
	new_child(shell, node, &info, i);
	i = 0;
	while (i <= info.n_pipes)
		waitpid(info.childs[i++], &shell->program_exit, 0);
	return (free(info.childs), 0);
}
