/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpereir <arpereir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:00:34 by hgutterr          #+#    #+#             */
/*   Updated: 2026/02/23 20:18:33 by arpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSE_H
# define MINISHELL_PARSE_H

# include "minishell.h"

t_token* 	new_token(t_token_type type, char *value);
void 		token_add_back(t_token **lst, t_token *node);
void 		handle_word(t_token **tokens, char *line, int *i, int preceded_by_space);
int 		handle_quote(t_token **tokens, char *line, int *i, int preceded_by_space);
void 		handle_operator(t_token **tokens, char *line, int *i, int preceded_by_space);

t_cmd*		parse(t_shell *shell, char *line);
t_token* 	tokenization(char *line);
int 		expand_tokens(t_shell *shell, t_token *tokens);

t_cmd* 		create_cmd_from_tokens(t_token *tokens);

int 		append_arg_with_quote(t_cmd *cmd, char *arg, int dquoted, int squoted);
int 		process_word_sequence(t_cmd *cmd, t_token **tokens);
int 		add_redir(t_redirs **list, t_token_type type, char *target, int expand);
t_cmd* 		parse_tokens_to_cmds(t_token *tokens);

t_cmd* 		new_cmd(void);
void 		add_cmd(t_cmd **list, t_cmd *cmd);
void 		free_cmd(t_cmd *cmd);
void 		free_cmds(t_cmd *cmds);

int 		syntax_check(t_token *tokens);
int 		ft_isredir(t_token_type type);

int 		exit_shell(t_token *tokens, int exit_code);
void 		free_tokens(t_token *tokens);

t_builtin	get_builtin_type(const char *cmd);

t_env* 		env_new(char *key, char *value);
void 		env_add_back(t_env **env, t_env *new);

t_env*		env_init(char **envp);
char* 		env_get(t_env *env, const char *key);

t_env*		env_dup(t_env *env);
void		env_free(t_env *env);

#endif
