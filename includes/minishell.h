/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 13:46:47 by hgutterr          #+#    #+#             */
/*   Updated: 2025/12/16 23:38:46 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft/libft.h"
# include "minishell_structs.h"

// token.c

t_token *new_token(t_token_type type, char *value);
void token_add_back(t_token **lst, t_token *new);
void handle_word(t_token **tokens, char *line, int *i);
void handle_quote(t_token **tokens, char *line, int *i);
void handle_operator(t_token **tokens, char *line, int *i);

#endif
