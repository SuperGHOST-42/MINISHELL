/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpereir <arpereir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 13:46:47 by hgutterr          #+#    #+#             */
/*   Updated: 2026/01/06 13:40:32 by arpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

# include "libft/libft.h"
# include "minishell_structs.h"

// token.c

t_token 	*new_token(t_token_type type, char *value);
void 		token_add_back(t_token **lst, t_token *new);
void 		handle_word(t_token **tokens, char *line, int *i);
int			handle_quote(t_token **tokens, char *line, int *i);
void 		handle_operator(t_token **tokens, char *line, int *i);

// tokenization
t_token 	*tokenization(char *line);

// syntax_checker.c

int 		syntax_check(t_token *tokens);
int 		ft_isredir(t_token_type type);

// exit.c

int			exit_shell(t_token *tokens, int exit_code);
void		free_tokens(t_token *tokens);

#endif
