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

int	init_ast(t_shell *shell)
{
	shell->ast = create_tree(shell->first, NULL);
	if (!shell->ast)
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		return (0);
	}
	return (1);
}

int	create_cmd(t_tree *node, t_token *start, t_token *end)
{
	int	control;

	control = 0;
	node->cmd = ft_calloc(1, sizeof(t_cmd));
	if (!node->cmd)
		return (perror("node->cmd malloc"), 0);
	while (start && start != end)
	{
		if (is_redir(start))
		{
			control = 1;
			if (start->next == end || start->next->type != T_WORD)
				return (free(node->cmd), 0);
			add_redir(&(node->cmd->redir), start, start->next);
			start = start->next;
		}
		else
			add_token_to_list(&(node->cmd->args),
				dup_token(start->value, start->type));
		if (control == 0)
			node->cmd->redir = NULL;
		start = start->next;
	}
	return (1);
}

t_tree	*create_tree(t_token *start, t_token *stop)
{
	t_tree	*node;
	t_token	*div;

	if (!start || start == stop)
		return (NULL);
	node = ft_calloc(1, sizeof(t_tree));
	if (!node)
		return (perror("node malloc"), NULL);
	div = div_point(start, stop);
	if (!div)
	{
		node->type = N_CMD;
		if (!create_cmd(node, start, stop))
			return (free(node), NULL);
		return (node);
	}
	node->cmd = NULL;
	node->type = is_div(div);
	node->left = create_tree(start, div);
	node->right = create_tree(div->next, stop);
	if (!(node->left) || !(node->right))
		return (free(node), NULL);
	return (node);
}
