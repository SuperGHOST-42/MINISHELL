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

// token.c

t_token 	*new_token(t_token_type type, char *value);
void 		token_add_back(t_token **lst, t_token *node);
void 		handle_word(t_token **tokens, char *line, int *i);
int			handle_quote(t_token **tokens, char *line, int *i);
void 		handle_operator(t_token **tokens, char *line, int *i);

// lex_line.c

void	    accept_line(t_shell *shell, char *line);
t_token 	*tokenization(char *line);

// exec.c

t_cmd	*create_cmd_from_tokens(t_token *tokens);
void	execute_simple_command(t_token *tokens, t_shell *shell);

/* parsing helpers */

int		append_arg(t_cmd *cmd, char *arg);
int		add_redir(t_redirs **list, t_token_type type, char *target);

/* build list of commands from tokens */

t_cmd	*parse_tokens_to_cmds(t_token *tokens);
void	free_cmds(t_cmd *cmds);
void	print_cmds(t_cmd *cmds);

// syntax_checker.c

int 		syntax_check(t_token *tokens);
int 		ft_isredir(t_token_type type);

// exit.c

int			exit_shell(t_token *tokens, int exit_code);
void		free_tokens(t_token *tokens);


#endif
