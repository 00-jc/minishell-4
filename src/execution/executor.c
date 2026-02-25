/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 16:48:33 by asoria            #+#    #+#             */
/*   Updated: 2026/02/25 01:41:54 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirs(t_cmd *cmd)
{
	t_redir	*current;
	int		control;

	if (!cmd->redir)
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
		if (!control)
			return (0);
		current = current->next;
	}
	return (1);
}

void	execute_external(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	pid_t	son;

	if (!cmd || !shell)
		return ;
	cmd->execute = tokens_to_args(cmd->args);
	setup_signals_running();
	son = fork();
	if (son == 0)
	{
		setup_signals_child();
		if (!cmd || !check_redirs(cmd) || !cmd->execute)
			exit(127);
		if (dup2_manager(cmd->redir) == 0)
			exit (126);
		path = search_cmd(cmd->execute[0], shell);
		if (!path)
		{
			perror("minishell");
			child_black_hole(shell);
			exit(127);
		}
		execve(path, cmd->execute, shell->envp);
		free(path);
		child_black_hole(shell);
		exit(127);
	}
}

void	execute_command(t_shell *shell, t_cmd *cmd)
{
	int	std_fd[2];

	if (is_builtin(cmd, shell->envp))
	{
		if (!redir_builtin(cmd, std_fd) || !dup2_manager(cmd->redir))
		{
			perror("minishell");
			return ;
		}
		execute_builtin(shell, cmd, &shell->envp);
		std_builtin(cmd, std_fd);
		return ;
	}
	execute_external(cmd, shell);
}

static void	wait_child(t_shell *shell)
{
	int		status;
	pid_t	son;

	son = wait(&status);
	if (son > 0)
	{
		if (WIFSIGNALED(status))
			shell->program_exit = 128 + WTERMSIG(status);
		else
			shell->program_exit = WEXITSTATUS(status);
	}
	if (g_signal == SIGINT)
	{
		write(1, "\n", 1);
		g_signal = 0;
	}
}

void	execute_pipeline(t_shell *shell)
{
	t_tree	*node;

	node = shell->ast;
	if (!node)
		return ;
	preprocess_heredocs(node);
	if (node->type == N_CMD)
	{
		execute_command(shell, node->cmd);
		if (!is_builtin(node->cmd, shell->envp))
			wait_child(shell);
		return ;
	}
	execute_pipe(shell, node);
}
