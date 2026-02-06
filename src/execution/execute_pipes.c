/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 11:39:16 by edblazqu          #+#    #+#             */
/*   Updated: 2026/02/06 11:39:17 by edblazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipes(t_tree *root)
{
	t_tree	*node;
	int		count;

	if (!root || root->type != N_PIPE)
		return (0);
	node = root;
	count = 0;
	while (node)
	{
		if (node->type == N_PIPE)
			count++;
		node = node->right;
	}
	return (count);
}

static void	new_child(t_tree *node, t_pipe *info, int i)
{
	t_cmd	*cmd;

	cmd = node->cmd;
	info->childs[i] = fork();
	if (info->childs[i] == 0)
	{

	}
}

void	execute_pipe(t_shell *shell, t_tree *node)
{
	t_pipe	info;
	int		i;

	info.n_pipes = count_pipes(node);
	info.childs = malloc(sizeof(pid_t) * info.n_pipes + 1);
	if (!info.childs)
		return ;
	info.prev_fd = -1;
	i = 0;
	while (i < info.n_pipes)
	{
		pipe(info.pipe_fd);
		new_child(node, &info, i);
		info.prev_fd = info.pipe_fd[0];
		close(info.pipe_fd[1]);
		node = node->right;
		i++;
	}
}
