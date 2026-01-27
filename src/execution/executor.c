/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 16:48:33 by asoria            #+#    #+#             */
/*   Updated: 2026/01/20 04:48:06 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	check_redirs(t_shell *shell, t_cmd *cmd)
{
	t_redir	*current;

	if (!cmd->redir)
		return ;
	current = cmd->redir;
	while (current)
	{
		if (current->type == T_INFILE)
			redir_infile(current);
		if (current->type == T_OUTFILE)
			redir_outfile(current);
		if (current->type == T_APPEND)
			redir_append(current);
		if (current->type == T_HEREDOC)
			redir_heredoc(current);
		current = current->next;
	}
} */

void	execute_external(t_cmd *cmd, char **envp, t_shell *sh)
{
	char	*path;
	int		n_tokens;
	pid_t	son;
	
	n_tokens = count_tokens(cmd->args);
	cmd->execute = tokens_to_args(cmd->args, 0, n_tokens);
	if (!cmd->execute)
		return ;
	son = fork();
	if (son == 0)
	{
		if (!cmd || !cmd->args)
			exit(127);
		path = search_cmd(cmd->execute[0], sh);
		if (!path)
		{
			perror("minishell");
			exit(127);
		}
		if (execve(path, cmd->execute, envp) == -1)
		{
			perror("execve");
			free(path);
			exit(127);
		}
	}
	waitpid(son, NULL, 0);
}

void	execute_command(t_shell *shell, t_cmd *cmd, char **envp)
{
	// check_redirs(shell, cmd);
	if (is_builtin(cmd, envp))
	{
		execute_builtin(shell, cmd, &envp);
		return ;
	}
	execute_external(cmd, envp, shell);
}

/* 
 * This functions skips AND and OR for easier AST implementation
 * in the future.
*/
void	execute_pipeline(t_shell *shell)
{
	t_tree	*node;

	node = shell->ast;
	if (!node)
		return ;
	if (node->type == N_CMD)
	{
		execute_command(shell, node->cmd, shell->envp);
		return ;
	}
}
