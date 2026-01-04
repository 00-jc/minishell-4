/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clusters.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 14:46:48 by asoria            #+#    #+#             */
/*   Updated: 2026/01/04 00:50:39 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*create_command(char **tokens, int start, int end, char *op)
{
	t_cmd	*cmd;
	int		i;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->arg_count = end - start + 1;
	cmd->args = malloc(sizeof(char *) * (cmd->arg_count + 1));
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	i = 0;
	while (i < cmd->arg_count)
	{
		cmd->args[i] = ft_strdup(tokens[start + i]);
		i++;
	}
	cmd->args[i] = NULL;
	cmd->operator = op;
	cmd->next = NULL;
	return (cmd);
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
	while (shell->token[i])
	{
		if (is_operator(shell->token[i]))
		{
			if (i > cmd_start)
			{
				cmd = create_command(shell->token, cmd_start,
						i - 1, shell->token[i]);
				add_command_to_list(&shell->cmd_list, cmd);
			}
			cmd_start = i + 1;
		}
		i++;
	}
	if (i > cmd_start)
	{
		cmd = create_command(shell->token, cmd_start, i - 1, NULL);
		add_command_to_list(&shell->cmd_list, cmd);
	}
}
