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

t_cmd	*create_cmd(t_tree *node, t_token *start, t_token *end)
{
	node->cmd = ft_calloc(1, sizeof(t_cmd));
	if (!node->cmd)
		return (perror("node->cmd malloc"), NULL);
	while (start != end)
	{
		if (is_redir(start))
		{
			if ((start + 1) == end || (start + 1)->type != T_WORD)
				return (free(node->cmd), NULL);
			add_redir(&(node->cmd->redir), start, start + 1);
		}
		else
		{
		}
		start++;
	}		
}

t_tree	*create_tree(t_token *start, t_token *stop)
{
	
}
