/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter-expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 05:29:37 by asoria            #+#    #+#             */
/*   Updated: 2026/02/24 16:24:46 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	var_len(const char *s)
{
	size_t	i;

	i = 0;
	if (!ft_isalpha(s[i]) && s[i] != '_')
		return (0);
	while (ft_isalnum(s[i]) || s[i] == '_')
		i++;
	return (i);
}

size_t	expanded_len(t_shell *sh, const char *s)
{
	size_t	i;
	size_t	len;
	size_t	vlen;
	char	*val;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			vlen = var_len(s + i + 1);
			val = ms_getenv(sh->envp, s + i + 1);
			if (val)
				len += ft_strlen(val);
			i += vlen + 1;
		}
		else
			len += ++i * 0 + 1;
	}
	return (len);
}

void	copy_expanded(t_shell *sh, char *dst, const char *s)
{
	while (*s)
	{
		if (*s == '$')
			handle_dollar(sh, &dst, &s);
		else
			*dst++ = *s++;
	}
	*dst = '\0';
}

void	expand_parameters(t_shell *shell, char **input)
{
	char	*out;
	size_t	len;

	if (!shell || !input || !*input)
		return ;
	len = expanded_len(shell, *input);
	out = malloc(len + 1);
	if (!out)
		return ;
	copy_expanded(shell, out, *input);
	free(*input);
	*input = out;
}
