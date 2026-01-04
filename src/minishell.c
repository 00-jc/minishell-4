/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 02:46:23 by asoria            #+#    #+#             */
/*   Updated: 2026/01/04 00:51:10 by asoria           ###   ########.fr       */
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
			break ;
		if (*shell->input)
		{
			tokenize_input(shell);
			clusterize_tokens(shell);
			execute_pipeline(shell);
			black_hole(shell);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	minishell(&shell, argv, envp);
	return (0);
}
