/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 06:32:00 by asoria            #+#    #+#             */
/*   Updated: 2026/01/11 03:18:25 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
static int	env_size(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}
*/
static int	find_var(char **envp, char *arg)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], arg, ft_strlen(arg) - 1 == 0))
			return (i);
		i++;
	}
	return (-1);
}

void	ms_unset(char *arg, char ***envp)
{
	int		index;
	int		size;
	char	**new_env;
	int	i;

	(void)new_env;
	(void)size;
	(void)i;
	if (!arg)
		return ;
	index = find_var(*envp, arg);
	if (index != -1)
	{
		printf("FOUND!\n");
	}
	else	
		printf("NOT FOUND!\n");
}
