/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:18:30 by asoria            #+#    #+#             */
/*   Updated: 2026/02/25 01:56:09 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_words(t_token *head)
{
	int	count;

	count = 0;
	while (head)
	{
		if (head->type == T_WORD)
			count++;
		head = head->next;
	}
	return (count);
}

char	**tokens_to_args(t_token *head)
{
	char	**args;
	int		i;

	args = malloc(sizeof(char *) * (count_words(head) + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (head)
	{
		if (head->type == T_WORD)
		{
			args[i] = ft_strdup(head->value);
			if (!args[i])
			{
				while (--i >= 0)
					free(args[i]);
				return (free(args), NULL);
			}
			i++;
		}
		head = head->next;
	}
	args[i] = NULL;
	return (args);
}
