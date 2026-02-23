/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 23:28:58 by edblazqu          #+#    #+#             */
/*   Updated: 2026/01/20 04:52:37 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dup_std(int std_fd[2])
{
	std_fd [0] = dup(STDOUT_FILENO);
	std_fd [1] = dup(STDIN_FILENO);
	if (std_fd[0] == -1 || std_fd[1] == -1)
		return (0);
	return (1);
}

int	redir_builtin(t_cmd *cmd, int std_fd[2])
{
	t_redir	*current;
	int		control;

	if (!cmd->redir || !dup_std(std_fd))
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

int	std_builtin(t_cmd *cmd, int std_fd[2])
{
	if (!cmd->redir)
		return (1);
	if (dup2(std_fd[0], STDOUT_FILENO) == -1)
		return (0);
	if (dup2(std_fd[1], STDIN_FILENO) == -1)
		return (0);
	close_pipes(std_fd);
	return (1);
}

int	is_builtin(t_cmd *cmd, char **envp)
{
	int					i;
	static const char	*builtins[] = {"pwd", "env", "cd", "echo",
		"export", "unset", "exit", NULL };

	(void)envp;
	i = 0;
	if (!cmd || !cmd->args || !cmd->args->value)
		return (0);
	while (builtins[i])
	{
		if (ft_strncmp(cmd->args->value, builtins[i], ft_strlen(builtins[i]))
			== 0 && cmd->args->value[ft_strlen(builtins[i])] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int	execute_builtin(t_shell *shell, t_cmd *cmd, char ***envp)
{
	if (ft_strcmp(cmd->args->value, "pwd") == 0)
		ms_pwd();
	else if (ft_strcmp(cmd->args->value, "env") == 0)
		ms_env(*envp);
	else if (ft_strcmp(cmd->args->value, "cd") == 0)
		ms_cd(cmd->args->next->value);
	else if (ft_strcmp(cmd->args->value, "echo") == 0)
		ms_echo(tokens_to_args(cmd->args, 0, count_tokens(cmd->args)));
	else if (ft_strcmp(cmd->args->value, "export") == 0)
		ms_export(cmd->args->next->value, envp);
	else if (ft_strcmp(cmd->args->value, "unset") == 0)
		ms_unset(envp, cmd->args->next->value);
	else if (ft_strcmp(cmd->args->value, "exit") == 0)
		ms_exit(shell, cmd->args->next);
	return (1);
}
