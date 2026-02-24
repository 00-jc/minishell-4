/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 15:59:03 by asoria            #+#    #+#             */
/*   Updated: 2026/02/24 17:21:36 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	dollar_len(t_shell *sh, const char *s, size_t *skip)
{
	char	*val;
	size_t	len;
	int		special;

	special = (*(s + 1) == '?');
	if (special)
	{
		val = ft_itoa(sh->program_exit);
		*skip = 2;
	}
	else
	{
		*skip = var_len(s + 1) + 1;
		val = ms_getenv(sh->envp, s + 1);
	}
	len = 0;
	if (val)
		len = ft_strlen(val);
	if (special)
		free(val);
	return (len);
}

void	handle_dollar(t_shell *sh, char **dst, const char **s)
{
	char	*val;
	char	*name;
	size_t	skip;

	if (*(*s + 1) == '?')
	{
		val = ft_itoa(sh->program_exit);
		skip = 2;
	}
	else
	{
		skip = var_len(*s + 1) + 1;
		name = ft_substr(*s + 1, 0, var_len(*s + 1));
		val = ms_getenv(sh->envp, name);
		free(name);
	}
	if (val)
	{
		ft_strcpy(*dst, val);
		*dst += ft_strlen(val);
	}
	if (*(*s + 1) == '?')
		free(val);
	*s += skip;
}
