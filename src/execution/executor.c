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

void	execute_external(t_cmd *cmd, char **envp, t_shell *sh)
{
	char	*path;

	if (!cmd || !cmd->args)
		exit(127);
	path = search_cmd(cmd->args->value, sh);
	if (!path)
		exit(127);
	if (execve(path, tokens_to_args(cmd->args, 0, count_tokens(cmd->args) - 1), envp) == -1)
	{
		free(path);
		exit(127);
	}
}

void	execute_command(t_shell *shell, t_cmd *cmd, char **envp)
{
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
	if (node->type == N_CMD)
	{
		execute_command(shell, node->cmd, shell->envp);
		return ;
	}
	else
	{

	}
}
