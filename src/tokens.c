/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 19:43:20 by asoria            #+#    #+#             */
/*   Updated: 2026/01/02 21:20:28 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*skip_whitespace(char *input)
{
	while (*input == ' ' || *input == '\t')
		input++;
	return (input);
}

static char	*get_token(t_shell *shell, int i)
{
	int		j;
	int		k;
	char	*start;

	start = shell->input;
	j = 0;
	while (*shell->input != ' ' && *shell->input != '\t'
		&& *shell->input != '\0')
	{
		shell->input++;
		j++;
	}
	shell->token[i].value = malloc(sizeof(char) * (j + 1));
	if (!shell->token[i].value)
		return (NULL);
	k = 0;
	while (k < j)
	{
		shell->token[i].value[k] = start[k];
		k++;
	}
	shell->token[i].value[j] = '\0';
	return (shell->input);
}

void	tokenize_input(t_shell *shell)
{
	int		i;
	char	*start;

	start = shell->input;
	shell->token = malloc(sizeof(t_token *) * MAX_TOKENS);
	if (!shell->token)
		return ;
	i = 0;
	while (*shell->input != '\0')
	{
		shell->input = skip_whitespace(shell->input);
		if (*shell->input == '\0')
			break ;
		get_token(shell, i);
		i++;
	}
	shell->token[i].value = NULL;
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
	if (ft_strncmp(token->value, "|", 2) == 0)
		return (token->type = T_PIPE, 1);
	if (ft_strncmp(token->value, ";", 2) == 0)
		return (token->type = T_ENDLINE, 1);
	if (ft_strncmp(token->value, ">", 2) == 0)
		return (token->type = T_OUTFILE, 1);
	if (ft_strncmp(token->value, "<", 2) == 0)
		return (token->type = T_INFILE, 1);
	if (ft_strncmp(token->value, "<<", 2) == 0)
		return (token->type = T_HEREDOC, 1);
	if (ft_strncmp(token->value, ">>", 2) == 0)
		return (token->type = T_APPEND, 1);
	token->type = T_WORD;
	return (0);
}
