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

void	execute_external(t_cmd *cmd, char **envp)
{
	char	*path;

	path = find_path(cmd->args[0], envp);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	if (execve(path, cmd->args, envp) == -1)
	{
		free(path);
		perror("execve");
		exit(126);
	}
}

void	execute_command(t_shell *shell, t_cmd *cmd, char **envp)
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
		execute_external(cmd, envp);
}

void	execute_pipeline(t_shell *shell)
{
	t_redirect	redir;
	t_cmd		*cmd;

	redir.n_child = count_commands(shell->cmd_list);
	cmd = shell->cmd_list;
	while (cmd)
	{
		
	}
}
