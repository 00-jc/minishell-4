/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 19:43:20 by asoria            #+#    #+#             */
/*   Updated: 2026/02/24 17:04:32 by asoria           ###   ########.fr       */
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
	char	*tmp;
	int	len;

	len = raw_token_len(shell->input);
	tmp = strip_quotes(shell->input, len);
	shell->input += len;
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
		classify_token(new);
		add_token_to_list(&shell->first, new);
		new = NULL;
	}
	shell->input = start;
}

int	classify_token(t_token *token)
{
	if (!token)
		return (0);
	if (ft_strncmp(token->value, "|", 1) == 0)
		return (token->type = T_PIPE, 1);
	if (ft_strncmp(token->value, "<<", 2) == 0)
		return (token->type = T_HEREDOC, 1);
	if (ft_strncmp(token->value, ">>", 2) == 0)
		return (token->type = T_APPEND, 1);
	if (ft_strncmp(token->value, ">", 1) == 0)
		return (token->type = T_OUTFILE, 1);
	if (ft_strncmp(token->value, "<", 1) == 0)
		return (token->type = T_INFILE, 1);
	token->type = T_WORD;
	return (0);
}
