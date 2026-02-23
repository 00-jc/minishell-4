/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:25:32 by edblazqu          #+#    #+#             */
/*   Updated: 2026/01/07 03:53:32 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_pwd(void)
{
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, PATH_MAX))
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", cwd);
	return (0);
}
