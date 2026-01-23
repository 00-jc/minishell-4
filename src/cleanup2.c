/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 05:36:59 by asoria            #+#    #+#             */
/*   Updated: 2026/01/20 05:37:00 by asoria           ###   ########.fr       */
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

void	free_ast(t_tree	*node)
{
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->cmd != NULL)
		free(node->cmd);
	free(node);
}

void	black_hole(t_shell *shell)
{
	if (shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
	free_tokens(&shell->ast->cmd->args);
	if (shell->path)
	{
		free_path(shell->path);
		shell->path = NULL;
	}
	free_ast(shell->ast);
	write_history(shell->history_file);
}
