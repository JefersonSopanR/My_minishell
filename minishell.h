/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-31 10:18:08 by jesopan-          #+#    #+#             */
/*   Updated: 2024-07-31 10:18:08 by jesopan-         ###   ########ç         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <limits.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <sys/signal.h>

typedef enum e_type
{
	T_WORD,
	T_O_PARENTHESIS,
	T_C_PARENTHESIS,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_REDIR_HEREDOC,
	T_PIPE,
	T_AND,
	T_OR,
}	t_token_type;

typedef struct s_token
{
	char			*data;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_OR,
	NODE_AND,
}	t_node_type;

typedef enum e_rror
{
	E_NONE,
	E_SYNTAX,
}	t_error;

typedef struct s_node
{
	t_node_type		type;
	t_redir			*redir;
	char			*data;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}	t_envp;

typedef struct s_global
{
	t_token		*cur_token;
	t_error		error_type;
	t_token		*token;
	t_node		*ast;
	t_envp		*envp;
	bool		quote;
	char		**dup_envp;
	int			stdin;
	int			stdout;
	char		*line;
	int			exit_status;
	int			i;
}	t_global;


int			ft_get_exit_status(int status);
//init

void		ft_procces_ast(t_global *minishell);
void		ft_init_minishell(char **env, t_global *minishell);
int			ft_readline(t_global *minishell);

//TOKENIZATION

bool		ft_check_awk(t_token **token);
void		ft_append_awk_arg(t_token **token, char *line, int *i);
void		ft_free_tokens(t_token **token);
t_token		*ft_get_tokens(char *line, t_global *minishell);
t_token		*ft_new_token(t_token_type type, char *data);
void		ft_add_back(t_token **token, t_token *new);
void		ft_free_tokens(t_token **token);
bool		ft_check_quotes(char *line);
void		ft_print_tokens(t_global *minishell);
void		ft_id_redir_input(t_token **token, char *line, int *i);
void		ft_id_redir_output(t_token **token, char *line, int *i);
void		ft_identify_redir(t_token **token, char *line, int *i);
void		ft_identify_parenthesis(t_token **token, char *line, int *i);
void		ft_identify_and_or(t_token **token, char *line, int *i);
void		ft_identify_operators(t_token **token, char *line, int *i);
int			ft_keep_in_quotes(char *line, int *i, char *quote, bool flag);
void		ft_append_word(t_token **token, char *line, t_global *minishell);
char		*ft_join_normal_data(char *line, char *data, char *quote, \
			t_global *minishell);
char		*ft_append_quoted_word(char *line, char quote, char *data, \
			t_global *minishell);
void		ft_prep_quote_word(t_token **token, char *line, char *data, \
			t_global *minishell);

//PARSING
t_node		*ft_new_node(t_node_type type);
t_redir		*ft_new_redir(t_global *minishell);
void		ft_add_redir_back(t_redir **redir, t_redir *new);
char		*ft_get_node_data(t_global *minishell);
bool		ft_is_not_op(char *line, int *i);
bool		ft_is_cmd(t_token *token);
bool		ft_is_redir(t_token_type type);
t_redir		*ft_fill_redir(t_redir **redir, t_global *minishell);
t_node		*ft_get_cmd_node(t_global *minishell);
t_node		*ft_primary(t_global *minishell);
t_node		*ft_expression(int min_prec, t_global *minishell);
t_node		*ft_create_ast(t_token *token, t_global *minishell);
void		ft_free_redir(t_redir *redir);
void		ft_free_cmd(t_node *ast);
void		ft_free_ast(t_node *ast);
t_node		*ft_connect_nodes(t_token_type op, t_node *left, t_node *right);
t_node_type	ft_convert_type(t_token_type op);
int			ft_prec(t_token_type type);
t_node		*ft_new_node(t_node_type type);

//EXECUTION
void		ft_command_not_found(char **split_command);
void		free_split(char **split);
char		*create_path(char *path, char *cmd);
char		*get_path(char *cmd, char **envp, t_global *minishell);
void		execute_command(char *command, char **envp, t_global *minishell);
int			get_here_doc(char *delimeter);
void		child_get_input(char *delimeter, int pfd[]);
int			ft_redir_append(char	*file);
int			ft_redir_out(char	*file);
int			ft_redir_in(char	*file);
int			ft_execute_command(t_node *node, t_global *minishell, bool in_pipe);
int			ft_execute_normal_cmd(t_node *node, t_global *minishell);
int			ft_check_redirections(t_redir	*redirect);
void		ft_child_process(t_node *node, char **envp, t_global *minishell);
int			ft_start_execution(t_node *ast, t_global *minishell, bool in_pipe);
void		ft_reset_fd(t_global *minishell, bool in_pipe);
void		ft_erro_pipe(void);
char		**ft_handle_cmd_quotes(char	*command);

//BUILTINS

void		ft_reset_shell(char **cmd, t_global *minishell, bool in_pipe);
int			ft_execute_builtin(t_node *node, t_global *minishell, bool in_pipe);
bool		ft_is_builtin(char *command);
int			ft_cd(char **cmd, t_global *minishell);
void		ft_cd_error(char *path);
void		ft_cd_error_dup(char *path);
int			ft_echo(char **cmd, t_global *minishell);
char		*ft_get_echo_quote(char *word);
int			ft_env(char **env, t_global *minishell);
int			ft_pwd(char **cmd);
int			ft_unset(char **cmd, t_global *minishell);
int			ft_expr(char **cmd, t_global *minishell);
int			ft_get_result(char **arg, t_global *minishell);
bool		ft_verify_arg(char **arg);
void		ft_msg_err_expr(char *msg);

//EXPORT

void		ft_export_key(char *cmd, t_global *minishell);
int			ft_export(char **cmd, t_global *minishell);
bool		ft_check_equal(char *key);
bool		ft_search_key(char *key, char *value, t_global *minishell);
void		ft_print_export(t_envp *envp);
void		ft_error_key(char *key);

//EXIT

void		ft_free_everything(char **cmd, int num, t_global *minishell);
int			ft_exit(char **cmd, t_global *minishell);
int			ft_count_args(char **cmd, int j, bool sign, t_global *minishell);
long		ft_exit_atoi(const char *s, char **cmd, t_global *minishell);
void		ft_numeric_argument_required(const char *s, char **cmd, \
			t_global *minishell);

//PRINTERS
void		ft_print_ast(t_node *ast, int depth);
void		ft_print_error(t_token *token, t_global *minishell);

//ENVP
t_envp		*ft_duplicate_envp(char **env, t_global *minishell);
void		ft_add_back_envp(t_envp **envp, t_envp *new);
t_envp		*ft_new_envp(char *key, char *value);
void		ft_free_envp(t_envp **envp);
void		ft_print_envp(t_envp *envp);
char		*ft_get_value(char *env);
char		*ft_get_key(char *env);

#endif
