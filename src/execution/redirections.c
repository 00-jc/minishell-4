/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:55:05 by edblazqu          #+#    #+#             */
/*   Updated: 2026/02/24 19:31:29 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_infile(t_redir *redir)
{
	int	fd;

	if (!redir->file.value)
		return (0);
	fd = open(redir->file.value, O_RDONLY);
	if (fd < 0)
		return (0);
	redir->fd = fd;
	return (1);
}

int	redir_outfile(t_redir *redir)
{
	int	fd;

	if (!redir->file.value)
		return (0);
	fd = open(redir->file.value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (0);
	redir->fd = fd;
	return (1);
}

int	redir_append(t_redir *redir)
{
	int	fd;

	if (!redir->file.value)
		return (0);
	fd = open(redir->file.value, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd < 0)
		return (0);
	redir->fd = fd;
	return (1);
}

