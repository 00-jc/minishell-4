/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 02:30:42 by asoria            #+#    #+#             */
/*   Updated: 2026/02/25 01:36:23 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*join;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	join = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!join)
		return (NULL);
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = '\0';
	free(s1);
	return (join);
}

int	is_environment_modifier(t_cmd *cmd)
{
	if (ft_strcmp(cmd->args->value, "export") == 0)
		return (1);
	if (ft_strcmp(cmd->args->value, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd->args->value, "exit") == 0)
		return (1);
	if (ft_strcmp(cmd->args->value, "cd") == 0)
		return (1);
	return (0);
}

void	slash_path(t_shell *shell)
{
	size_t	i;
	void	*tmp;

	i = 0;
	while (shell->path[i] != NULL)
	{
		tmp = ft_strjoin_free(shell->path[i], "/");
		if (tmp)
			shell->path[i] = tmp;
		i++;
	}
}

int	count_tokens(t_token *tokens)
{
	int		i;
	t_token	*current;

	if (!tokens)
		return (-1);
	i = 0;
	current = tokens;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}
