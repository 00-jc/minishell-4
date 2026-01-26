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

void	ms_exit(t_shell *shell, t_token *arg)
{
	int	exit_code;

	exit_code = 0;
	if (arg)
		exit_code = ft_atoi(arg->value);
	printf("exit\n");
	shell->is_alive = 0;
	shell->exit_code = exit_code;
}
