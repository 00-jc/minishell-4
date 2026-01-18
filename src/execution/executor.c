/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 16:48:33 by asoria            #+#    #+#             */
/*   Updated: 2026/01/18 23:40:12 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_external(t_cmd *cmd, t_redir *redir, char **envp, t_shell *shell)
{
	char	*path;

	(void)redir;
	if (!cmd || !cmd->args || !cmd->args[0])
		exit(127);
	path = search_cmd(cmd->args[0], shell);
	if (!path)
		exit(127);
	if (execve(path, cmd->args, envp) == -1)
	{
		if (path != cmd->args[0])
			free(path);
		exit(127);
	}
}

void	execute_command(t_shell *shell, t_cmd *cmd, char **envp)
{
	int	pid;
	int	status;
	char	**temp_envp;

	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	if (is_builtin(cmd, envp))
	{
		temp_envp = envp;
		execute_builtin(shell, cmd, &temp_envp);
		shell->exit_code = 0;
		return ;
	}
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
		execute_external(cmd, cmd->redir, envp, shell);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_code = WEXITSTATUS(status);
}

/* 
 * This functions skips AND and OR for easier AST implementation
 * in the future.
*/
void	execute_pipeline(t_shell *shell)
{
	t_cmd	*current;

	current = shell->cmd_list;
	while (current)
	{
		if (current->operator == T_AND ||
			current->operator == T_OR ||
			current->operator == T_PIPE)
		{
			current = current->next;
			continue ;
		}
		execute_command(shell, current, shell->envp);
		current = current->next;
	}
}
