/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 12:14:35 by edblazqu          #+#    #+#             */
/*   Updated: 2026/01/18 23:34:34 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(const t_token *token)
{
	if (token->type == T_APPEND || token->type == T_HEREDOC)
		return (1);
	if (token->type == T_OUTFILE || token->type == T_INFILE)
		return (1);
	return (0);
}

int	add_redir(t_redir **redir, t_token *redir_token, t_token *next)
{
	t_redir	*new;
	t_redir	*idx;

	new = ft_calloc(1, sizeof(t_redir));
	if (!new)
		return (0);
	new->type = redir_token->type;
	new->file.type = next->type;
	new->file.value = ft_strdup(next->value);
	if (!new->file.value)
		return (free(new), 0);
	new->file.next = NULL;
	new->next = NULL;
	if (!(*redir) || !redir)
		(*redir) = new;
	else
	{
		idx = *redir;
		while (idx->next != NULL)
			idx = idx->next;
		idx->next = new;
	}
	return (1);
}

t_node_type	is_div(t_token *token)
{
	if (!token)
		return (N_CMD);
	if (token->type == T_PIPE)
		return (N_PIPE); 
	if (token->type == T_AND)
		return (N_AND);
	if (token->type == T_OR)
		return (N_OR);
	if (token->type == T_ENDLINE)
		return (N_ENDLINE);
	return (N_CMD);
}

t_token	*div_point(t_token *start, t_token *stop)
{
	t_token	*div;

	if (!start)
		return (NULL);
	div = NULL;
	while (start && start != stop)
	{
		if (start->type == T_OR || start->type == T_AND)
			div = start;
		if (start->type == T_PIPE)
		{
			div = start;
			break ;
		}
		start = start->next;
	}
	return (div);
}
