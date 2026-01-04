/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:41:52 by asoria            #+#    #+#             */
/*   Updated: 2026/01/04 21:42:32 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(char *token)
{
	if (!token)
		return (0);
	if (ft_strncmp(token, "&&", MAX_BUFFER) == 0)
		return (1);
	if (ft_strncmp(token, "||", MAX_BUFFER) == 0)
		return (1);
	if (ft_strncmp(token, "|", MAX_BUFFER) == 0)
		return (1);
	if (ft_strncmp(token, ";", MAX_BUFFER) == 0)
		return (1);
	if (ft_strncmp(token, ">", MAX_BUFFER) == 0)
		return (1);
	if (ft_strncmp(token, "<", MAX_BUFFER) == 0)
		return (1);
	if (ft_strncmp(token, ">>", MAX_BUFFER) == 0)
		return (1);
	if (ft_strncmp(token, "<<", MAX_BUFFER) == 0)
		return (1);
	return (0);
}
