/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 18:49:10 by asoria            #+#    #+#             */
/*   Updated: 2026/01/09 06:01:44 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_new_dir(char *dir_name)
{
	char	*cwd;
	char	*temp;
	char	*new_dir;

	if (dir_name[0] == '/')
		return (ft_strdup(dir_name));
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	temp = ft_strjoin(cwd, "/");
	free(cwd);
	if (!temp)
		return (NULL);
	new_dir = ft_strjoin(temp, dir_name);
	free(temp);
	return (new_dir);
}

char	*ms_cd(char *arg)
{
	char	*new_dir;

	new_dir = get_new_dir(arg);
	if (chdir(new_dir) == 1)
	{
		perror("cd");
		free(new_dir);
		return (NULL);
	}
	free(new_dir);
	return (NULL);
}
