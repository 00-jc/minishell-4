/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clusters.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 14:46:48 by asoria            #+#    #+#             */
/*   Updated: 2026/01/18 13:20:31 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_tokens_range(t_token *head, int start, int end)
{
	t_token	*current;
	int		i;
	int		count;

	current = head;
	i = 0;
	count = 0;
	while (current && i <= end)
	{
		if (i >= start && i <= end)
			count++;
		current = current->next;
		i++;
	}
	return (count);
}

static char	**tokens_to_args(t_token *head, int start, int end)
{
	char	**args;
	t_token	*current;
	int		i;
	int		j;

	args = malloc(sizeof(char *) * (count_tokens_range(head, start, end) + 1));
	if (!args)
		return (NULL);
	current = head;
	i = 0;
	j = 0;
	while (current && i <= end)
	{
		if (i >= start && i <= end && current->type == T_WORD)
		{
			args[j] = ft_strdup(current->value);
			if (!args[j])
				return (NULL);
			j++;
		}
		current = current->next;
		i++;
	}
	args[j] = NULL;
	return (args);
}

static t_cmd	*create_command(t_token *tokens, int start, int end,
				t_token_type op)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = tokens_to_args(tokens, start, end);
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	cmd->operator = op;
	cmd->redir = NULL;
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
