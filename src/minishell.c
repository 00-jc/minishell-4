/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 02:46:23 by asoria            #+#    #+#             */
/*   Updated: 2026/01/07 03:51:02 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(t_shell *shell, char **argv, char **envp)
{
	init_shell(argv, envp, shell);
	while (1)
	{
		read_input(shell);
		if (!shell->input)
		{
			black_hole(shell);
			free_envp(&shell->envp);
			break ;
		}
		else if (*shell->input)
		{
			tokenize_input(shell);
			clusterize_tokens(shell);
			execute_pipeline(shell);
			black_hole(shell);
		}
	}
	free_envp(&shell->envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	minishell(&shell, argv, envp);
	return (0);
}
