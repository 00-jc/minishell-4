/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 02:46:23 by asoria            #+#    #+#             */
/*   Updated: 2026/02/24 18:29:39 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(t_shell *shell, char **argv, char **envp)
{
	init_shell(argv, envp, shell);
	while (shell->is_alive)
	{
		setup_signals_interactive();
		read_input(shell);
		process_input(shell);
		black_hole(shell);
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
