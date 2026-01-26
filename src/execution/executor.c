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
	int		n_tokens;
	pid_t	son;
	
	n_tokens = count_tokens(cmd->args);
	if (n_tokens == -1)
	{
		perror("n_tokens ");
		return ;
	}
	cmd->execute = tokens_to_args(cmd->args, 0, n_tokens);
	if (!cmd->execute)
		printf("Pues son los argumentos");
	son = fork();
	if (son == 0)
	{
		if (!cmd || !cmd->args)
			exit(127);
		path = search_cmd(cmd->args->value, sh);
		if (!path)
		{
			perror("minishell: ");
			exit(127);
		}
		if (execve(path, cmd->execute, envp) == -1)
		{
			perror("execve: ");
			free(path);
			exit(127);
		}
	}
	waitpid(son, NULL, 0);
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
	if (!node)
		return ;
	if (node->type == N_CMD)
	{
		execute_command(shell, node->cmd, shell->envp);
		return ;
	}
	else
	{

	}
}
