/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 13:06:27 by asoria            #+#    #+#             */
/*   Updated: 2026/02/24 18:31:26 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* WIP: Will extract custom PS1 from ".msrc" config file */
char	*get_prompt(t_shell *shell)
{
	(void)shell;
	return ("\033[32mStudent@42\033[34m - $ \033[0m");
}

void	process_input(t_shell *shell)
{
	if (!shell->input)
		return ;
	expand_parameters(shell, &shell->input);
	refresh_path(shell);
	tokenize_input(shell);
	if (init_ast(shell))
		execute_pipeline(shell);
}

void	read_input(t_shell *shell)
{
	shell->input = readline(shell->prompt);
	if (!shell->input)
	{
		shell->is_alive = 0;
		return ;
	}
	if (*shell->input)
		add_history(shell->input);
	else
	{
		free(shell->input);
		shell->input = NULL;
	}
}
