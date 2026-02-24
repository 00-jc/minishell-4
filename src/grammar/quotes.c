/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 16:55:42 by asoria            #+#    #+#             */
/*   Updated: 2026/02/24 16:56:06 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	raw_token_len(char *s)
{
	char	q;
	int		i;

	q = 0;
	i = 0;
	while (s[i])
	{
		if (!q && (s[i] == '\'' || s[i] == '"'))
			q = s[i];
		else if (q && s[i] == q)
			q = 0;
		else if (!q && (s[i] == ' ' || s[i] == '\t'))
			break ;
		i++;
	}
	return (i);
}

char	*strip_quotes(char *s, int len)
{
	char	*out;
	char	q;
	int		i;
	int		j;

	out = malloc(len + 1);
	if (!out)
		return (NULL);
	q = 0;
	i = 0;
	j = 0;
	while (i < len)
	{
		if (!q && (s[i] == '\'' || s[i] == '"'))
			q = s[i];
		else if (q && s[i] == q)
			q = 0;
		else
			out[j++] = s[i];
		i++;
	}
	out[j] = '\0';
	return (out);
}
