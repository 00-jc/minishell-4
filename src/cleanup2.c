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
	int	i;

	i = 0;
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->cmd != NULL)
	{
		free_tokens(&node->cmd->args);
		if (node->cmd->execute != NULL)
		{
			while (node->cmd->execute[i] != NULL)
			{
				free(node->cmd->execute[i]);
				i++;
			}
		}
		free(node->cmd->execute);
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
		shell->ast = NULL;
	}
	free_tokens(&(shell->first));
	write_history(shell->history_file);
}
