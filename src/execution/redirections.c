/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:55:05 by edblazqu          #+#    #+#             */
/*   Updated: 2026/02/24 17:57:37 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*put_name(void)
{
	static int	n;
	char		*result;

	result = ft_strjoin(".heredoc_", ft_itoa(n));
	n++;
	if (!result)
	{
		perror("minishell");
		return (NULL);
	}
	return (result);
}

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

int	redir_heredoc(t_redir *redir)
{
	int		fd;
	char	*read;

	redir->heredoc_name = put_name();
	if (!redir->heredoc_name)
	{
		perror("heredoc");
		return (0);
	}
	fd = open(redir->heredoc_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	redir->fd = open(redir->heredoc_name, O_RDONLY);
	if (fd < 0 || redir->fd < 0)
		return (0);
	while (1)
	{
		read = readline("> ");
		if (ft_strcmp(redir->file.value, read) == 0)
			break ;
		ft_putstr_fd(read, fd);
		ft_putstr_fd("\n", fd);
		free(read);
	}
	free(read);
	close(fd);
	return (1);
}
