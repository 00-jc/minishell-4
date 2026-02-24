/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 00:48:30 by asoria            #+#    #+#             */
/*   Updated: 2026/02/24 18:17:28 by asoria           ###   ########.fr       */
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

void	print_export(char **envp)
{
	char	*equal;
	int	i;

	i = 0;
	while (envp[i])
	{
		equal = ft_strchr(envp[i], '=');
		if (equal)
			printf("declare -x %.*s=\"%s\"\n",
				(int)(equal - envp[i]), envp[i], equal + 1);
		else
			printf("declare -x %s\n", envp[i]);
		i++;
	}
}

int	ms_export(char *arg, char ***envp)
{
	int		index;
	int		size;
	char	**new_env;
	char	**old_env;
	int		i;

	if (!arg)
		return (print_export(*envp), 0);
	size = env_size(*envp);
	new_env = malloc(sizeof(char *) * (size + 2));
	if (!new_env)
		return (1);
	index = find_var(*envp, arg);
	if (index != -1)
		return (free((*envp)[index]),
		(void)((*envp)[index] = ft_strdup(arg)),
		free(new_env), 0);
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
	return (free(old_env), 0);
}
