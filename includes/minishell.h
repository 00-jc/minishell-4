/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 02:47:47 by asoria            #+#    #+#             */
/*   Updated: 2026/01/20 04:55:31 by asoria           ###   ########.fr       */
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

typedef enum e_node_type
{
	N_CMD,
	N_PIPE,
	N_OR,
	N_AND,
	N_ENDLINE
}	t_node_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	t_token_type	type;
	t_token			file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**execute;
	t_token			*args;
	t_redir			*redir;
}					t_cmd;

typedef struct s_tree
{
	t_node_type		type;
	t_cmd			*cmd;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

typedef struct s_shell
{
	int		is_alive;
	int		exit_code;
	char	**envp;
	char	**path;
	char	*prompt;
	char	*input;
	t_token	*first;
	t_tree	*ast;
	char	*config_file;
	char	*history_file;
}		t_shell;

/* init.c */
void		refresh_path(t_shell *shell);
void		process_input(t_shell *shell);
int			init_shell(char **argv, char **envp, t_shell *shell);

/* parsing.c */
char		*get_prompt(t_shell *shell);
void		read_input(t_shell *shell);

/* debug.c */
void		print_cmd_list(t_cmd *cmd_list);
void		print_envp(t_shell *shell);

/* cleanup.c */
void		free_envp(char ***envp);
void		free_path(char **path);
void		free_tokens(t_token **list);
void		free_split(t_token **list);
void		black_hole(t_shell *shell);

/* parser/parser_utils.c */
int			is_redir(const t_token *token);
int			add_redir(t_redir **redir, t_token *redir_token, t_token *next);
t_node_type	is_div(t_token *token);
t_token		*div_point(t_token *start, t_token *stop);

/* parser/parser.c */
int			create_cmd(t_tree *node, t_token *start, t_token *end);
t_tree		*create_tree(t_token *start, t_token *stop);

/* execution/executor.c  */
int		is_builtin(t_cmd *cmd, char **envp);
void	execute_pipeline(t_shell *shell);
int		execute_builtin(t_shell *shell, t_cmd *cmd, char ***envp);
void	execute_external(t_cmd *cmd, char **envp, t_shell *shell);
void	execute_command(t_shell *shell, t_cmd *cmd, char **envp);
int		count_commands(t_cmd *cmd_list);

/* execution/executor_utils.c */
char		*search_cmd(char *cmd, t_shell *shell);

/* execution/pipes.c */

int			dup2_manager(int fd_stdout, int fd_stdin);
void		close_pipes(int pipe[2]);

/* token/tokens_utils.c */
t_token		*dup_token(char *value, t_token_type type);
t_token		*new_token(char *value);
void		add_token_to_list(t_token **lst, t_token *new);

/* tokens.c */
void		tokenize_input(t_shell *shell);

/* clusters.c */
char		**tokens_to_args(t_token *head, int start, int end);
int			classify_token(t_token *token);

/* builtin.c */
int			is_builtin(t_cmd *cmd, char **envp);

/* parameter-expansion.c */
void	expand_parameters(t_shell *shell, char **input);

/* cd.c */
char		*ms_cd(char *arg);

/* pwd.c */
void		ms_pwd(void);

/* env.c */
void		ms_env(char **envp);

/* echo.c */
void		ms_echo(char **args);

/* export.c */
void		ms_export(char *arg, char ***envp);

/* unset.c */
int			ms_unset(char ***envp, const char *var_name);

/* exit.c */
void		ms_exit(t_shell *shell, t_token *arg);

/* utils.c */
int			is_environment_modifier(t_cmd *cmd);
int			count_commands(t_cmd *cmd_list);
void		slash_path(t_shell *shell);
int			count_tokens(t_token *tokens);

char		*ms_getenv(char**envp, const char *name);
t_token		*last_token(t_token	*start);

#endif
