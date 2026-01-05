/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 21:15:11 by asoria            #+#    #+#             */
/*   Updated: 2026/01/03 18:15:08 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return ;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

void	free_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*current;
	t_cmd	*next;

	current = cmd_list;
	while (current)
	{
		next = current->next;
		if (current->args)
			free(current->args);
		free(current);
		current = next;
	}
}

void	free_envp(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell->envp)
	{
		while (shell->envp[i])
		{
			free(shell->envp[i]);
			i++;
		}
		free(shell->envp);
	}
}

void	black_hole(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell->input)
		free(shell->input);
	if (shell->token)
	{
		while (shell->token[i].value)
		{
			free(shell->token[i].value);
			i++;
		}
		free(shell->token);
	}
	free_cmd_list(shell->cmd_list);
	shell->cmd_list = NULL;
	write_history(shell->history_file);
}
