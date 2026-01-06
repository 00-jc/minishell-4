/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:25:32 by edblazqu          #+#    #+#             */
/*   Updated: 2026/01/06 02:20:29 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* WIP: THIS IS NOT THE FINISHED FUNCTION, IT ACCEPTS NO ARGUMENTS, IT IS
 * UNCOMPLETE */
void	ms_pwd(void)
{
	printf("%s\n", getcwd(NULL, 0));
}
