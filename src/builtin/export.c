/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 00:48:30 by asoria            #+#    #+#             */
/*   Updated: 2026/01/20 04:45:00 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_size(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

static int	find_var(char **envp, char *arg)
{
	int		i;
	char	*equal;
	size_t	name_len;

	equal = ft_strchr(arg, '=');
	if (!equal)
		return (-1);
	name_len = equal - arg;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], arg, name_len) == 0
			&& envp[i][name_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	ms_export(char *arg, char ***envp)
{
	int		index;
	int		size;
	char	**new_env;
	char	**old_env;
	int		i;

	size = env_size(*envp);
	new_env = malloc(sizeof(char *) * (size + 2));
	if (!arg || !new_env)
		return ;
	index = find_var(*envp, arg);
	if (index != -1)
	{
		free((*envp)[index]);
		(*envp)[index] = ft_strdup(arg);
		return ;
	}
	i = 0;
	while (i < size)
	{
		new_env[i] = (*envp)[i];
		i++;
	}
	new_env[i] = ft_strdup(arg);
	new_env[i + 1] = NULL;
	old_env = *envp;
	*envp = new_env;
	free(old_env);
}
