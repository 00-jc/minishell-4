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

int	is_builtin(t_cmd *cmd, char **envp)
{
	int					i;
	static const char	*builtins[] = {"pwd", "env", "cd", "echo",
		"export", "unset", "exit", NULL };

	(void)envp;
	i = 0;
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	while (builtins[i])
	{
		if (ft_strncmp(cmd->args[0], builtins[i], ft_strlen(builtins[i]))
			== 0 && cmd->args[0][ft_strlen(builtins[i])] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int	execute_builtin(t_shell *shell, t_cmd *cmd, char ***envp)
{
	if (ft_strcmp(cmd->args[0], "pwd") == 0 && cmd->args[0][3] == '\0')
		ms_pwd();
	else if (ft_strcmp(cmd->args[0], "env") == 0 && cmd->args[0][3] == '\0')
		ms_env(*envp);
	else if (ft_strcmp(cmd->args[0], "cd") == 0 && cmd->args[0][2] == '\0')
		ms_cd(cmd->args[1]);
	else if (ft_strcmp(cmd->args[0], "echo") == 0 && cmd->args[0][4] == '\0')
		ms_echo(cmd->args);
	else if (ft_strcmp(cmd->args[0], "export") == 0 && cmd->args[0][6] == '\0')
		ms_export(cmd->args[1], envp);
	else if (ft_strcmp(cmd->args[0], "unset") == 0 && cmd->args[0][5] == '\0')
		ms_unset(envp, cmd->args[1]);
	else if (ft_strcmp(cmd->args[0], "exit") == 0 && cmd->args[0][4] == '\0')
		ms_exit(shell, cmd->args[1]);
	return (1);
}
