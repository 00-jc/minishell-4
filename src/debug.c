/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 17:07:48 by asoria            #+#    #+#             */
/*   Updated: 2026/01/18 13:57:11 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char 	*get_operator_string(t_token_type op)
{
	if (op == T_PIPE)
		return ("|");
	if (op == T_AND)
		return ("&&");
	if (op == T_OR)
		return ("||");
	if (op == T_ENDLINE)
		return (";");
	return ("");
}

void	print_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*current;
	int		i;
	int		cmd_num;

	current = cmd_list;
	cmd_num = 1;
	while (current)
	{
		printf("Command %d: [", cmd_num);
		i = 0;
		while (current->args[i])
		{
			printf("%s", current->args[i]);
			if (current->args[i + 1])
				printf(" ");
			i++;
		}
		printf("]");
		if (current->operator != T_WORD)
			printf(" %s", get_operator_string(current->operator));
		printf("\n");
		current = current->next;
		cmd_num++;
	}
}

void	print_envp(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
	{
		printf("%s\n", shell->envp[i]);
		i++;
	}
}
