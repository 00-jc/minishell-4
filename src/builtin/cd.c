/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 18:49:10 by asoria            #+#    #+#             */
/*   Updated: 2026/01/09 05:12:13 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static char	*get_new_dir(char *dir_name)
{
}
*/
char	*ms_cd(char *arg)
{
	char	old_wd[PATH_MAX];
	char	new_wd[PATH_MAX];

	if (!getcwd(old_wd, PATH_MAX))
	{
		perror("cwd");
		return (NULL);
	}
	printf("old_wd: %s\n", old_wd);

(void)arg;
//	new_wd = get_new_dir(argv[1]);
	chdir("/home/$USER");
	
	getcwd(new_wd, PATH_MAX);
	printf("new_wd: %s\n", new_wd);
	return (NULL);
}
