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
