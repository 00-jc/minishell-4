/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 19:27:52 by asoria            #+#    #+#             */
/*   Updated: 2026/02/24 19:31:21 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *put_name(void)
{
	static int	n;
	char		*num;
	char		*result;

	num = ft_itoa(n);
	if (!num)
		return (NULL);
	result = ft_strjoin(".heredoc_", num);
	free(num);
	n++;
	if (!result)
	{
		perror("minishell");
		return (NULL);
	}
	return (result);
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
		if (!read || ft_strcmp(redir->file.value, read) == 0)
			break ;
		ft_putstr_fd(read, fd);
		ft_putstr_fd("\n", fd);
		free(read);
	}
	free(read);
	close(fd);
	return (1);
}

void	preprocess_heredocs(t_tree *node)
{
	t_redir	*redir;

	if (!node)
		return ;
	preprocess_heredocs(node->left);
	preprocess_heredocs(node->right);
	if (node->type != N_CMD)
		return ;
	redir = node->cmd->redir;
	while (redir)
	{
		if (redir->type == T_HEREDOC)
			redir_heredoc(redir);
		redir = redir->next;
	}
}
