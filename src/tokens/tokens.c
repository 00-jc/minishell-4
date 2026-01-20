/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 19:43:20 by asoria            #+#    #+#             */
/*   Updated: 2026/01/18 23:39:24 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*skip_whitespace(char *input)
{
	while (*input == ' ' || *input == '\t')
		input++;
	return (input);
}

static char	*get_token(t_shell *shell)
{
	int		i;
	int		j;
	char	*start;
	char	*tmp;

	start = shell->input;
	i = 0;
	while (*shell->input != ' ' && *shell->input != '\t'
		&& *shell->input != '\0')
	{
		shell->input++;
		i++;
	}
	tmp = malloc(sizeof(char) * (i + 1));
	if (!tmp)
		return (NULL);
	j = 0;
	while (j < i)
	{
		tmp[j] = start[j];
		j++;
	}
	tmp[i] = '\0';
	return (tmp);
}

void	tokenize_input(t_shell *shell)
{
	char	*start;
	t_token	*new;

	start = shell->input;
	while (*shell->input != '\0')
	{
		shell->input = skip_whitespace(shell->input);
		if (*shell->input == '\0')
			break ;
		new = new_token(get_token(shell));
		add_token_to_list(&shell->first, new);
		new = NULL;
	}
	shell->last = last_token(shell->first);
	shell->input = start;
}

int	classify_token(t_token *token)
{
	if (!token)
		return (0);
	if (ft_strncmp(token->value, "&&", 2) == 0)
		return (token->type = T_AND, 1);
	if (ft_strncmp(token->value, "||", 2) == 0)
		return (token->type = T_OR, 1);
	if (ft_strncmp(token->value, "|", 1) == 0)
		return (token->type = T_PIPE, 1);
	if (ft_strncmp(token->value, ";", 1) == 0)
		return (token->type = T_ENDLINE, 1);
	if (ft_strncmp(token->value, ">", 1) == 0)
		return (token->type = T_OUTFILE, 1);
	if (ft_strncmp(token->value, "<", 1) == 0)
		return (token->type = T_INFILE, 1);
	if (ft_strncmp(token->value, "<<", 2) == 0)
		return (token->type = T_HEREDOC, 1);
	if (ft_strncmp(token->value, ">>", 2) == 0)
		return (token->type = T_APPEND, 1);
	token->type = T_WORD;
	return (0);
}
