/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 12:27:15 by edblazqu          #+#    #+#             */
/*   Updated: 2026/01/16 12:27:15 by edblazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(char *value)
{
	t_token	*new;

	if (!value)
		return (NULL);
	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = value;
	new->next = NULL;
	return (new);
}

void	add_token_to_list(t_token **lst, t_token *new)
{
	t_token	*idx;

	if (!lst)
	{
		*lst = new;
		return ;
	}
	idx = *lst;
	while (idx->next != NULL)
		idx = idx->next;
	idx->next = new;
}
