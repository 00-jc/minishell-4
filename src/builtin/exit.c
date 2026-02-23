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

static int	is_numeric(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (i);
}

void	ms_exit(t_shell *shell, t_token *arg)
{
	printf("exit\n");
	if (!arg)
	{
		shell->is_alive = 0;
		shell->exit_code = shell->program_exit;
		return ;
	}
	if (!is_numeric(arg->value))
	{
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		shell->is_alive = 0;
		shell->exit_code = 2;
		return ;
	}
	if (arg->next)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return ;
	}
	shell->is_alive = 0;
	shell->exit_code = ft_atoi(arg->value) % 256;
}
