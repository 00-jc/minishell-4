/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 16:48:33 by asoria            #+#    #+#             */
/*   Updated: 2026/01/11 03:21:48 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	new_child(t_redir *redir, int fd_pipe[2], size_t i, char **envp)
{
	redir->child[i] = fork();
	if (redir->child[i] == 0)
	{
		if (i == 0)
			dup2_manager(fd_pipe[1], redir->fd[0]);
		else if (i == redir->n_child - 1)
			dup2_manager(redir->fd[1], redir->prev_fd);
		else
			dup2_manager(fd_pipe[1], redir->prev_fd);
		if (i != 0)
			close(redir->prev_fd);
		close_pipes(redir->fd);
		close_pipes(fd_pipe);
		execve();
	}
	else if (redir->child[i] < 0)
		
}

void	execute_external(t_shell *shell, t_redir *redir, char **envp)
{
	if (!execve(search_cmd(redir->now_route[0], shell), redir->now_route, envp))
		exit (127);
}

void	execute_command(t_shell *shell, t_redir *redir, char **envp)
{
	char	**temp_envp;

	if (!cmd || !cmd->args || !cmd->args[0])
		exit(127);
	if (is_builtin(cmd, envp))
	{
		temp_envp = envp;
		execute_builtin(shell, cmd, &temp_envp);
		exit(0);
	}
	else
		execute_external(shell, redir, envp);
}

void	execute_pipeline(t_shell *shell)
{
	t_redir	redir;
	t_cmd		*cmd;
	char		*route;

	init_redir(&redir);
	cmd = shell->cmd_list;
	while (cmd)
	{
		redir.now_route = cmd->args;
		execute_command(shell, cmd, shell->envp);
		cmd = cmd->next;
	}
}
