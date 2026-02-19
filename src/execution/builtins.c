/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 23:28:58 by edblazqu          #+#    #+#             */
/*   Updated: 2026/02/19 22:54:34 by asoria           ###   ########.fr       */
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

static char	*next_value(t_token *token)
{
	if (token && token->next)
		return (token->next->value);
	return (NULL);
}

int	execute_builtin(t_shell *shell, t_cmd *cmd, char ***envp)
{
	if (ft_strcmp(cmd->args->value, "pwd") == 0)
		ms_pwd();
	else if (ft_strcmp(cmd->args->value, "env") == 0)
		ms_env(*envp);
	else if (ft_strcmp(cmd->args->value, "cd") == 0)
		ms_cd(next_value(cmd->args));
	else if (ft_strcmp(cmd->args->value, "echo") == 0)
		ms_echo(tokens_to_args(cmd->args, 0, count_tokens(cmd->args)));
	else if (ft_strcmp(cmd->args->value, "export") == 0)
		ms_export(next_value(cmd->args), envp);
	else if (ft_strcmp(cmd->args->value, "unset") == 0)
		ms_unset(envp, next_value(cmd->args));
	else if (ft_strcmp(cmd->args->value, "exit") == 0)
		ms_exit(shell, cmd->args->next);
	return (1);
}
