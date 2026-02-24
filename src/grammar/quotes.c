/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 16:55:42 by asoria            #+#    #+#             */
/*   Updated: 2026/02/24 18:35:40 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	raw_token_len(char *s)
{
	char	q;
	int		i;

	if (s[0] == '|')
		return (1);
	if ((s[0] == '>' || s[0] == '<') && s[1] == s[0])
		return (2);
	if (s[0] == '>' || s[0] == '<')
		return (1);
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
		else if (!q && (s[i] == '|' || s[i] == '>' || s[i] == '<'))
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
