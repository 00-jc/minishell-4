/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 02:30:42 by asoria            #+#    #+#             */
/*   Updated: 2026/01/11 02:35:44 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_environment_modifier(t_cmd *cmd)
{
	if (ft_strncmp(cmd->args[0], "export", ft_strlen(cmd->args[0])) == 0)
		return (1);
	if (ft_strncmp(cmd->args[0], "unset", ft_strlen(cmd->args[0])) == 0)
		return (1);
	if (ft_strncmp(cmd->args[0], "exit", ft_strlen(cmd->args[0])) == 0)
		return (1);
	if (ft_strncmp(cmd->args[0], "cd", ft_strlen(cmd->args[0])) == 0)
		return (1);
	return (0);
}
