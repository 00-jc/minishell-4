/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 02:30:42 by asoria            #+#    #+#             */
/*   Updated: 2026/01/18 23:50:24 by asoria           ###   ########.fr       */
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
	if (ft_strncmp(cmd->args[0], "export", 6) == 0 && cmd->args->value[6] == '\0')
		return (1);
	if (ft_strncmp(cmd->args[0], "unset", 5) == 0 && cmd->args->value[5] == '\0')
		return (1);
	if (ft_strncmp(cmd->args[0], "exit", 4) == 0 && cmd->args->value[4] == '\0')
		return (1);
	if (ft_strncmp(cmd->args[0], "cd", 2) == 0 && cmd->args->value[2] == '\0')
		return (1);
	return (0);
}

int	count_commands(t_cmd *cmd_list)
{
	int		count;
	t_cmd	*current;

	count = 0;
	current = cmd_list;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

void	slash_path(t_shell *shell)
{
	size_t	i;

	i = 0;
	while (shell->path[i] != NULL)
	{
		shell->path[i] = ft_strjoin_free(shell->path[i], "/");
		i++;
	}
}

int	count_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		i++;
		tokens = tokens->next;
	}
	return (i);
}
