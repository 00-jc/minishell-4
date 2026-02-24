/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter-expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 05:29:37 by asoria            #+#    #+#             */
/*   Updated: 2026/02/24 17:02:42 by asoria           ###   ########.fr       */
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

static char	update_quote(char q, char c)
{
	if (c != '\'' && c != '"')
		return (q);
	if (q == 0)
		return (c);
	if (q == c)
		return (0);
	return (q);
}

size_t	expanded_len(t_shell *sh, const char *s)
{
	size_t	i;
	size_t	len;
	size_t	skip;
	char	q;

	i = 0;
	len = 0;
	q = 0;
	while (s[i])
	{
		if (s[i] == '$' && q != '\'')
		{
			len += dollar_len(sh, s + i, &skip);
			i += skip;
		}
		else
		{
			q = update_quote(q, s[i]);
			len++;
			i++;
		}
	}
	return (len);
}

void	copy_expanded(t_shell *sh, char *dst, const char *s)
{
	char	q;

	q = 0;
	while (*s)
	{
		if (*s == '$' && q != '\'')
			handle_dollar(sh, &dst, &s);
		else
		{
			q = update_quote(q, *s);
			*dst++ = *s++;
		}
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
