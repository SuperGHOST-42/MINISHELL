/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:00:34 by hgutterr          #+#    #+#             */
/*   Updated: 2026/01/07 17:00:34 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSE_H
# define MINISHELL_PARSE_H

# include "minishell.h"

t_token*new_token(t_token_type type, char *value);
voidtoken_add_back(t_token **lst, t_token *node);
voidhandle_word(t_token **tokens, char *line, int *i);
inthandle_quote(t_token **tokens, char *line, int *i);
voidhandle_operator(t_token **tokens, char *line, int *i);

t_cmd*parse(t_shell *shell, char *line);
t_token*tokenization(char *line);

t_cmd*create_cmd_from_tokens(t_token *tokens);
voidexecute_simple_command(t_token *tokens, t_shell *shell);

intappend_arg(t_cmd *cmd, char *arg);
intadd_redir(t_redirs **list, t_token_type type, char *target);
t_cmd*parse_tokens_to_cmds(t_token *tokens);
voidprint_cmds(t_cmd *cmds);

t_cmd*new_cmd(void);
voidadd_cmd(t_cmd **list, t_cmd *cmd);
voidfree_cmd(t_cmd *cmd);
voidfree_cmds(t_cmd *cmds);

intsyntax_check(t_token *tokens);
intft_isredir(t_token_type type);

intexit_shell(t_token *tokens, int exit_code);
voidfree_tokens(t_token *tokens);

t_builtinget_builtin_type(const char *cmd);
intexecute_builtin(t_cmd *cmd, t_shell *shell);

voidft_echo(char *str);
voidft_cd(char *path);
voidft_pwd(void);
voidft_export(char *key, char *value);
voidft_unset(char *key);

t_env*env_new(char *key, char *value);
voidenv_add_back(t_env **env, t_env *new);

t_env*env_init(char **envp);
char*env_get(t_env *env, const char *key);

t_env*env_dup(t_env *env);
voidenv_free(t_env *env);

#endif
