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

char	**tokens_to_args(t_token *head, int start, int end)
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
