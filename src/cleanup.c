/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 21:15:11 by asoria            #+#    #+#             */
/*   Updated: 2026/01/18 23:15:22 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token **lst)
{
	t_token	*tmp;
	t_token *current;

	if (!lst || !(*lst))
		return ;
	current = *lst;
	while (current)
	{
		tmp = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = tmp;
	}
	*lst = NULL;
}

static void	free_redir_list(t_redir **redir)
{
	t_redir	*current;
	t_redir	*next;

	if (!redir || !*redir)
		return ;
	current = *redir;
	while (current)
	{
		next = current->next;
		if (current->file.value)
			free(current->file.value);
		free(current);
		current = next;
	}
	*redir = NULL;
}

void	free_cmd_list(t_cmd **cmd_list)
{
	int	i;
	t_cmd	*current;
	t_cmd	*next;

	if (!cmd_list || !*cmd_list)
		return ;
	current = *cmd_list;
	while (current)
	{
		next = current->next;
		if (current->args)
		{
			i = 0;
			while (current->args[i])
				free(current->args[i++]);
			free(current->args);
		}
		if (current->redir)
			free_redir_list(&current->redir);
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

void	free_path(char **path)
{
	size_t	i;

	if (!path)
		return ;
	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}

void	black_hole(t_shell *shell)
{
	if (shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
	free_tokens(&shell->tokens);
	if (shell->path)
	{
		free_path(shell->path);
		shell->path = NULL;
	}
	free_cmd_list(&shell->cmd_list);
	write_history(shell->history_file);
}
