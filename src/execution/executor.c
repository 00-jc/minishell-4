/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 16:48:33 by asoria            #+#    #+#             */
/*   Updated: 2026/01/18 14:16:17 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_external(t_cmd *cmd, t_redir *redir, char **envp)
{
	char	*path;

	(void)redir;
	(void)envp;
	if (!cmd || !cmd->args || !cmd->args[0])
		exit(127);
	path = search_cmd(cmd->args[0], NULL);
	if (execve(path, cmd->args, envp) == -1)
		exit(127);
}

void	execute_command(t_shell *shell, t_cmd *cmd, char **envp)
{
	int	pid;
	int	status;
	char	**temp_envp;

	if (!cmd || !cmd->args || !cmd->args[0])
		ms_exit(shell, "127");
	if (is_builtin(cmd, envp))
	{
		temp_envp = envp;
		execute_builtin(shell, cmd, &temp_envp);
		ms_exit(shell, "0");
	}
	pid = fork();
	if (pid == 1)
		return ;
	if (pid == 0)
		execute_external(cmd, cmd->redir, envp);
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
		if (current->operator == T_AND)
		{
			current = current->next;
			continue ;
		}
		if (current->operator == T_OR)
		{
			current = current->next;
			continue ;
		}
		execute_command(shell, current, shell->envp);
		current = current->next;
	}
}
