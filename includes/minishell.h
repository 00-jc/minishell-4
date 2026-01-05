/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 02:47:47 by asoria            #+#    #+#             */
/*   Updated: 2026/01/04 21:45:14 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

# define MAX_TOKENS 1000
# define MAX_BUFFER 4096

typedef enum e_token_type
{
	T_WORD,
	T_ENDLINE,
	T_PIPE,
	T_INFILE,
	T_OUTFILE,
	T_APPEND,
	T_HEREDOC,
	T_AND,
	T_OR
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

typedef struct s_cmd
{
	char			**args;
	int				arg_count;
	char			*operator;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_shell
{
	char	**envp;
	char	*prompt;
	char	*input;
	t_token	*token;
	t_cmd	*cmd_list;
	char	*config_file;
	char	*history_file;
}		t_shell;

typedef struct s_redirect
{
	int		prev_fd;
	int		heredoc;
	int		fd[2];
	pid_t	*child;
}	t_redirect;

/* init.c */
char	*find_path(char *cmd, char **envp);
int		init_shell(char **argv, char **envp, t_shell *shell);

/* parsing.c */
char	*get_prompt(t_shell *shell);
void	read_input(t_shell *shell);

/* debug.c */
void	print_cmd_list(t_cmd *cmd_list);
void	print_envp(t_shell *shell);

/* cleanup.c */
void	free_split(char **tokens);
void	free_cmd_list(t_cmd *cmd_list);
void	black_hole(t_shell *shell);

/* executing.c  */
void	execute_pipeline(t_shell *shell);
void	process_input(t_shell *shell);

/* tokens.c */
void	tokenize_input(t_shell *shell);

/* clusters.c */
int		typify_token(t_token *token);
void	clusterize_tokens(t_shell *shell);

/* cd.c */
char	*ms_cd(t_shell *shell);

/* test.c */
void	test_print(void);

/* pipes */
void	setup_pipe_fds(t_cmd *cmd, int prev_fd, int pipe_fd[2]);

#endif
