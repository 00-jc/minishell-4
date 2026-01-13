/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 23:28:58 by edblazqu          #+#    #+#             */
/*   Updated: 2026/01/13 23:28:59 by edblazqu         ###   ########.fr       */
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
