/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 21:15:11 by asoria            #+#    #+#             */
/*   Updated: 2026/01/18 12:03:02 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token **lst)
{
	t_token	*tmp;

	if (!lst || !(*lst))
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
}

void	free_cmd_list(t_cmd **cmd_list)
{
	t_cmd	*current;
	t_cmd	*next;

	if (!cmd_list || !*cmd_list)
		return ;
	current = *cmd_list;
	while (current)
	{
		next = current->next;
		if (current->args)
			free_split(current->tokens);
		free(current);
		current = next;
	}
	*cmd_list = NULL;
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

void	free_split(t_token **token)
{
	int	i;

	if (!token || !*token)
		return ;
	i = 0;
	while ((*token)[i].value)
	{
		free((*token)[i].value);
		i++;
	}
	free(*token);
	*token = NULL;
}

void	free_path(char ***path)
{
	size_t	i;

	i = 0;
	while ((*path)[i])
	{
		free((*path)[i]);
	}
	free(*path);
	*path = NULL;
}

void	black_hole(t_shell *shell)
{
	if (shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
	free_tokens(&shell->token);
	free_path(shell->path);
	free_cmd_list(&shell->cmd_list);
	write_history(shell->history_file);
}
