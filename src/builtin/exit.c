/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 02:27:07 by asoria            #+#    #+#             */
/*   Updated: 2026/01/11 02:29:35 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exit(char *arg)
{
	int	exit_code;

	exit_code = 0;
	if (arg)
	{
		exit_code = ft_atoi(arg);
	}
	printf("exit\n");
	exit(exit_code);
}
