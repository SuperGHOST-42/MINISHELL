/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:00:34 by hgutterr          #+#    #+#             */
/*   Updated: 2026/01/31 18:02:43 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSE_H
# define MINISHELL_PARSE_H

# include "minishell.h"

t_token* new_token(t_token_type type, char *value);
void token_add_back(t_token **lst, t_token *node);
void handle_word(t_token **tokens, char *line, int *i);
int handle_quote(t_token **tokens, char *line, int *i);
void handle_operator(t_token **tokens, char *line, int *i);

t_cmd* parse(t_shell *shell, char *line);
t_token* tokenization(char *line);

t_cmd* create_cmd_from_tokens(t_token *tokens);
void execute_simple_command(t_token *tokens, t_shell *shell);

int append_arg(t_cmd *cmd, char *arg);
int add_redir(t_redirs **list, t_token_type type, char *target);
t_cmd* parse_tokens_to_cmds(t_token *tokens);
void print_cmds(t_cmd *cmds);

t_cmd* new_cmd(void);
void add_cmd(t_cmd **list, t_cmd *cmd);
void free_cmd(t_cmd *cmd);
void free_cmds(t_cmd *cmds);

int syntax_check(t_token *tokens);
int ft_isredir(t_token_type type);

int exit_shell(t_token *tokens, int exit_code);
void free_tokens(t_token *tokens);

t_builtin get_builtin_type(const char *cmd);
int execute_builtin(t_cmd *cmd, t_shell *shell);

void ft_echo(char *str);
void ft_cd(char *path);
void ft_pwd(void);
void ft_export(char *key, char *value);
void ft_unset(char *key);
void ft_env(t_shell *shell);
void ft_exit(t_shell *shell, char *exit_code_str);

t_env* env_new(char *key, char *value);
void env_add_back(t_env **env, t_env *new);

t_env* env_init(char **envp);
char* env_get(t_env *env, const char *key);

t_env* env_dup(t_env *env);
void env_free(t_env *env);

#endif
