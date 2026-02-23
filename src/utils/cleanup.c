/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 21:15:11 by asoria            #+#    #+#             */
/*   Updated: 2026/01/20 04:35:14 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token **lst)
{
	t_token	*tmp;
	t_token	*current;

	if (!lst || !(*lst))
		return ;
	current = *lst;
	while (current)
	{
		tmp = current->next;
		free(current->value);
		free(current);
		current = tmp;
	}
	*lst = NULL;
}

void	free_envp(char ***envp)
{
	int	i;

	if (!envp || !*envp)
		return ;
	i = 0;
	while ((*envp)[i])
	{
		free((*envp)[i]);
		i++;
	}
	free(*envp);
	*envp = NULL;
}
