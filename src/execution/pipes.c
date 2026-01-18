/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:29:39 by edblazqu          #+#    #+#             */
/*   Updated: 2026/01/18 13:34:29 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dup2_manager(int fd_stdout, int fd_stdin)
{
	if (dup2(fd_stdout, STDOUT_FILENO) == -1)
		return (0);
	if (dup2(fd_stdin, STDIN_FILENO) == -1)
		return (0);
	return (1);
}

void	close_pipes(int pipe[2])
{
	close(pipe[0]);
	close(pipe[1]);
}
