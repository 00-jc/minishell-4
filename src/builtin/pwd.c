/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:25:32 by edblazqu          #+#    #+#             */
/*   Updated: 2026/01/05 13:25:34 by edblazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	int	i;

	(void)ac;
	(void)av;
	i = 0;
	if (!env)
		return (1);
	while (ft_strncmp(env[i], "PWD", 3) != 0)
		i++;
	if (!env[i])
		return (1);
	printf("%s\n", env[i] + 4);
	return (0);
}
