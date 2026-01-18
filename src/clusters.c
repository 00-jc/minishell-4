/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clusters.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 14:46:48 by asoria            #+#    #+#             */
/*   Updated: 2026/01/18 12:29:19 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*create_command(t_token	*token, int start, int end,
				t_token_type op)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->token_count = end - start + 1;
	cmd->tokens = malloc(sizeof(t_token) * (cmd->token_count + 1));
	if (!cmd->tokens)
	{
		free(cmd);
		return (NULL);
	}
	cmd->next = NULL;
	return (cmd);
}

static void	add_tokens(t_cmd *cmd, t_token *token)
{
	int	i;

	i = 0;
	while (i < cmd->token_count)
	{
		
	}
}

static void	add_command_to_list(t_cmd **list, t_cmd *new_cmd)
{
	t_cmd	*last;

	if (!new_cmd)
		return ;
	if (!*list)
	{
		*list = new_cmd;
		return ;
	}
	last = *list;
	while (last->next)
		last = last->next;
	last->next = new_cmd;
}

void	clusterize_tokens(t_shell *shell)
{
	int		i;
	int		cmd_start;
	t_cmd	*cmd;

	i = 0;
	cmd_start = 0;
	while (shell->token[i].value != NULL)
	{
		if (classify_token(&(shell->token[i])) && i > cmd_start)
		{
			cmd = create_command(shell->token, cmd_start,
					i - 1, shell->token[i].type);
			add_command_to_list(&shell->cmd_list, cmd);
			cmd_start = i + 1;
		}
		i++;
	}
	if (i > cmd_start)
	{
		cmd = create_command(shell->token, cmd_start, i - 1, 0);
		add_command_to_list(&shell->cmd_list, cmd);
	}
}
