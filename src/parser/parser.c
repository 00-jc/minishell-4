/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:32:09 by edblazqu          #+#    #+#             */
/*   Updated: 2026/01/15 15:32:10 by edblazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_cmd(t_tree *node, t_token *start, t_token *end)
{
	node->cmd = ft_calloc(1, sizeof(t_cmd));
	if (!node->cmd)
		return (perror("node->cmd malloc"), NULL);
	while (start != end)
	{
		if (is_redir(start))
		{
			if (start->next == end || start->next->type != T_WORD)
				return (free(node->cmd), NULL);
			add_redir(&(node->cmd->redir), start, start + 1);
		}
		else
			add_token_to_list(node->cmd->args, start);
		start = start->next;
	}
	return (start);	
}

t_tree	*create_tree(t_token *start, t_token *stop)
{
	t_tree	*node;

	if (!start || !stop || start == stop)
		return (NULL);
	node = ft_calloc(1, sizeof(t_tree));
	if (!node)
		return (perror("node malloc"), NULL);
	while (start != stop)
	{
		if ()
	}
	return (node);
}
