/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 21:15:11 by asoria            #+#    #+#             */
/*   Updated: 2026/01/07 02:06:05 by asoria           ###   ########.fr       */
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
	cmd_list = NULL;
}

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	if (envp)
	{
		while (envp[i])
		{
			free(envp[i]);
			i++;
		}
		free(envp);
	}
}

void	free_tokens(t_token *token)
{
	int	i;

	i = 0;
	if (token)
	{
		while (token[i].value)
		{
			free(token[i].value);
			i++;
		}
		free(token);
	}
}

void	black_hole(t_shell *shell)
{
	if (shell->input)
		free(shell->input);
	free_tokens(shell->token);
	free_cmd_list(shell->cmd_list);
	free_envp(shell->envp);
	write_history(shell->history_file);
}
