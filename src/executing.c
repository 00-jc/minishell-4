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
	if (ft_strncmp("pwd", cmd->args[0], 3) == 0)
		return (1);
	if (ft_strncmp("env", cmd->args[0], 3) == 0)
		return (1);
	if (ft_strncmp("cd", cmd->args[0], 2) == 0)
		return (1);
	if (ft_strncmp("echo", cmd->args[0], 4) == 0)
		return (1);
	if (ft_strncmp("export", cmd->args[0], 6) == 0)
		return (1);
	if (ft_strncmp("unset", cmd->args[0], 5) == 0)
		return (1);
	if (ft_strncmp("exit", cmd->args[0], 4) == 0)
		return (1);
	return (0);
}

int	execute_builtin(t_shell *shell, t_cmd *cmd, char ***envp)
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
		ms_exit(shell, cmd->args[1]);
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
	int		prev_fd;
	int		pipe_fd[2];
	t_cmd	*cmd;

	if (!shell->cmd_list)
		return ;
	prev_fd = -1;
	cmd = shell->cmd_list;
	while (cmd)
	{
		if (is_environment_modifier(cmd) &&
				(!cmd->operator || ft_strncmp(cmd->operator, "|", 1) != 0))
			execute_builtin(shell, cmd, &shell->envp);
		else
		{
			if (cmd->operator && ft_strncmp(cmd->operator, "|", 1) == 0)
				pipe(pipe_fd);
			if (fork() == 0)
			{
				setup_pipe_fds(cmd, prev_fd, pipe_fd);
				execute_command(shell, cmd, shell->envp);
				exit(0);
			}
			if (prev_fd != -1)
				close(prev_fd);
			check_if_pipe(cmd->operator, &prev_fd, &pipe_fd);
		}
		cmd = cmd->next;
	}
	while (wait(NULL) > 0)
		;
}
