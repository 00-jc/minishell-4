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

int	is_builtin(t_cmd *cmd, char **envp)
{
	(void)envp;
	if (strncmp("pwd", cmd->args[0], 3) == 0)
		return (1);
	if (strncmp("env", cmd->args[0], 3) == 0)
		return (1);
	if (strncmp("cd", cmd->args[0], 2) == 0)
		return (1);
	if (strncmp("echo", cmd->args[0], 4) == 0)
		return (1);
	if (strncmp("export", cmd->args[0], 6) == 0)
		return (1);
	if (strncmp("unset", cmd->args[0], 5) == 0)
		return (1);
	if (strncmp("exit", cmd->args[0], 4) == 0)
		return (1);
	return (0);
}

int	execute_builtin(t_cmd *cmd, char ***envp)
{
	(void)envp;
	if (ft_strncmp(cmd->args[0], "pwd", 3) == 0)
		ms_pwd();
	if (ft_strncmp(cmd->args[0], "env", 3) == 0)
		ms_env(*envp);
	if (ft_strncmp(cmd->args[0], "cd", 2) == 0)
		ms_cd(cmd->args[1]);
	if (ft_strncmp(cmd->args[0], "echo", 4) == 0)
		ms_echo(cmd->args[1], cmd->args[2]);
	if (ft_strncmp(cmd->args[0], "export", 6) == 0)
		ms_export(cmd->args[1], envp);
	if (ft_strncmp(cmd->args[0], "unset", 5) == 0)
		ms_unset(cmd->args[1], envp);
	if (ft_strncmp(cmd->args[0], "exit", 4) == 0)
		ms_exit(cmd->args[1]);
	return (1);
}

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

void	execute_command(t_cmd *cmd, char **envp)
{
	char	**temp_envp;

	if (!cmd || !cmd->args || !cmd->args[0])
		exit(127);
	if (is_builtin(cmd, envp))
	{
		temp_envp = envp;
		execute_builtin(cmd, &temp_envp);
		exit(0);
	}
	else
		execute_external(cmd, envp);
}

int	count_commands(t_cmd *cmd_list)
{
	int		count;
	t_cmd	*current;

	count = 0;
	current = cmd_list;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}
