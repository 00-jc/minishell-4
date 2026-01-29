/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:55:05 by edblazqu          #+#    #+#             */
/*   Updated: 2026/01/27 16:55:06 by edblazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_infile(const t_redir *redir)
{
	int	fd;

	if (!redir->file.value)
		return (-1);
	fd = open(redir->file.value, O_RDONLY);
	if (fd < 0)
		return (-1);
	return (fd);
}

int	redir_outfile(const t_redir *redir)
{
	int	fd;

	if (!redir->file.value)
		return (-1);
	fd = open(redir->file.value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	return (fd);
}

int	redir_append(const t_redir *redir)
{
	int	fd;

	if (!redir->file.value)
		return (-1);
	fd = open(redir->file.value, O_APPEND, 0644);
	if (fd < 0)
		return (-1);
	return (fd);
}
