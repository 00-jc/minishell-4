/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 02:46:23 by asoria            #+#    #+#             */
/*   Updated: 2026/01/20 04:26:13 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_alive(t_shell *shell)
{
	if (shell->is_alive)
	{
		setup_signals_interactive();
		read_input(shell);
		expand_parameters(shell, &shell->input);
	}
}

void	minishell(t_shell *shell, char **argv, char **envp)
{
	init_shell(argv, envp, shell);
	while (1)
	{
		check_alive(shell);
		if (*shell->input)
		{
			refresh_path(shell);
			tokenize_input(shell);
			if (init_ast(shell))
				execute_pipeline(shell);
			black_hole(shell);
		}
	}
	black_hole(shell);
	free_envp(&shell->envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	minishell(&shell, argv, envp);
	return (shell.exit_code);
}
