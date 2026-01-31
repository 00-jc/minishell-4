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
	fd = open(redir->file.value, O_APPEND, 0644);
	if (fd < 0)
		return (0);
	redir->fd = fd;
	return (1);
}

int	redir_heredoc(t_redir *redir)
{
	int		fd;
	char	*read;

	if (!redir->file.value) // ESTO NO FURULA ASI, NECESITO CREAR EL NOMBRE DEL ARCHIVO YO Y PONERLES NUMERACION PORQUE SI NO PETARA
		return (0);
	fd = open(redir->file.value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (0);
	while (1)
	{
		read = readline(">");
		/* REDIR->FILE.VALUE NO ES LO CORRECTO PERO TIENE SENTIDO
		PORQUE ASI USAS DIRECTAMENTE LO QUE VA EN LA POSI DEL ARCHIVO */
		if (ft_strcmp(redir->file.value, read) == 0)
			break ;
		ft_putstr_fd(read, fd);
		free(read);
	}
	free(read);
	return (1);
}
