/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 06:32:00 by asoria            #+#    #+#             */
/*   Updated: 2026/01/18 19:15:25 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	find_env_index(char **envp, const char *name)
{
	int	i;
	size_t	len;

	if (!envp || !*name)
		return (-1);
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return(i);
		i++;
	}
	return (-1);
}

static void	remove_env_var(char **envp, int index)
{
	free(envp[index]);
	while (envp[index])
	{
		envp[index] = envp[index + 1];
		index++;
	}
}

int	ms_unset(char ***envp, const char *var_name)
{
	int	idx;

	if (!envp || !*envp || !var_name)
		return (1);
	if (!is_valid_identifier(var_name))
		return (1);
	idx = find_env_index(*envp, var_name);
	if (idx != -1)
		remove_env_var(*envp, idx);
	return (0);
}
