/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 16:48:33 by asoria            #+#    #+#             */
/*   Updated: 2026/01/29 16:51:22 by asoria           ###   ########.fr       */
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
		else if (current->type == T_HEREDOC)
			control = redir_heredoc(current);
		if (!control)
			return (0);	
		current = current->next;
	}
	return (1);
}

void	execute_external(t_cmd *cmd, char **envp, t_shell *sh)
{
	char	*path;
	pid_t	son;
	
	cmd->execute = tokens_to_args(cmd->args, 0, count_tokens(cmd->args));
	son = fork();
	if (son == 0)
	{
		if (!cmd || !check_redirs(cmd) || !cmd->execute)
			exit(127);
		if (dup2_manager(cmd->redir) == 0)
			exit (126);
		path = search_cmd(cmd->execute[0], sh);
		if (!path)
		{
			perror("minishell");
			exit(127);
		}
		if (execve(path, cmd->execute, envp) == -1)
		{
			perror("minishell");
			free(path);
			exit(127);
		}
	}
}

void	execute_command(t_shell *shell, t_cmd *cmd)
{
	if (is_builtin(cmd, shell->envp))
	{
		execute_builtin(shell, cmd, &shell->envp);
	}
	execute_external(cmd, shell->envp, shell);
}

/* 
 * This functions skips AND and OR for easier AST implementation
 * in the future.
*/
void	execute_pipeline(t_shell *shell)
{
	t_tree	*node;
	pid_t	last_child;

	node = shell->ast;
	if (!node)
		return ;
	if (node->type == N_CMD)
	{
		execute_command(shell, node->cmd);
		wait(&last_child);
		shell->program_exit = WEXITSTATUS(last_child);
		return ;
	}
	else
		execute_pipe(shell, node);
	while (wait(&last_child) > 0)
		;
	shell->program_exit = WEXITSTATUS(last_child);
}
