/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 16:48:33 by asoria            #+#    #+#             */
/*   Updated: 2026/01/06 01:28:16 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_cmd *cmd, char **envp)
{
	(void)envp;
	if (strncmp("pwd", cmd->args[0], 3) == 0)
		return (1);
	return (0);
}

int	execute_builtin(t_cmd *cmd, char **envp)
{
	(void)envp;
	if (ft_strncmp(cmd->args[0], "pwd", 3) == 0)
		return (ms_pwd());
	return(1);
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

static void	execute_command(t_cmd *cmd, char **envp)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		exit(127);
	if (is_builtin(cmd, envp))
		execute_builtin(cmd, envp);
	else if (!is_builtin(cmd, envp))
		execute_external(cmd, envp);
}

static int	count_commands(t_cmd *cmd_list)
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

void	execute_pipeline(t_shell *shell)
{
	t_cmd	*cmd;
	int		pipe_fd[2];
	int		prev_fd;
	pid_t	*pids;
	int		i;
	int		cmd_count;

	if (!shell->cmd_list)
		return ;
	cmd_count = count_commands(shell->cmd_list);
	pids = malloc(sizeof(pid_t) * cmd_count);
	if (!pids)
		return ;
	cmd = shell->cmd_list;
	prev_fd = -1;
	i = 0;
	while (cmd)
	{
		if (cmd->operator && ft_strncmp(cmd->operator, "|", 1) == 0)
		{
			if (pipe(pipe_fd) == -1)
			{
				perror("pipe");
				free(pids);
				return ;
			}
		}
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("fork");
			if (prev_fd != -1)
				close(prev_fd);
			if (cmd->operator && ft_strncmp(cmd->operator, "|", 1) == 0)
			{
				close(pipe_fd[0]);
				close(pipe_fd[1]);
			}
			free(pids);
			return ;
		}
		if (pids[i] == 0)
		{
			setup_pipe_fds(cmd, prev_fd, pipe_fd);
			execute_command(cmd, shell->envp);
		}
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->operator && ft_strncmp(cmd->operator, "|", 1) == 0)
		{
			close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
		}
		else
			prev_fd = -1;
		cmd = cmd->next;
		i++;
	}
	i = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
	free(pids);
}
