/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 05:36:59 by asoria            #+#    #+#             */
/*   Updated: 2026/02/24 15:34:59 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_path(char **path)
{
	size_t	i;

	if (!path)
		return ;
	i = 0;
	while (path[i])
		free(path[i++]);
	free(path);
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
		if (current->heredoc_name)
			free(current->heredoc_name);
		free(current);
		current = next;
	}
	*redir = NULL;
}

void	free_ast(t_tree	*node)
{
	int	i;

	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->cmd != NULL)
	{
		free_tokens(&node->cmd->args);
		free_redir_list(&node->cmd->redir);
		if (node->cmd->execute != NULL)
		{
			i = 0;
			while (node->cmd->execute[i] != NULL)
				free(node->cmd->execute[i++]);
			free(node->cmd->execute);
		}
		free(node->cmd);
	}
	free(node);
}

void	black_hole(t_shell *shell)
{
	if (shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
	if (shell->path)
	{
		free_path(shell->path);
		shell->path = NULL;
	}
	if (shell->ast)
	{
		free_ast(shell->ast);
		shell->ast = NULL;
	}
	free_tokens(&(shell->first));
	write_history(shell->history_file);
	g_signal = 0;
}

void	child_black_hole(t_shell *shell)
{
	if (shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
	if (shell->path)
	{
		free_path(shell->path);
		shell->path = NULL;
	}
	if (shell->ast)
	{
		free_ast(shell->ast);
		shell->ast = NULL;
	}
	free_tokens(&(shell->first));
	free_envp(&shell->envp);
	write_history(shell->history_file);
	g_signal = 0;
}
