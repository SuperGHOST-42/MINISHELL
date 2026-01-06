/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 13:46:41 by hgutterr          #+#    #+#             */
/*   Updated: 2026/01/06 16:52:42 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H

# include "minishell.h"

typedef enum e_token_type
{
	WORD,
	PIPE,
	R_IN, 			// <
	R_OUT,			// >
	R_APP,			// >>
	R_HEREDOC		// <<
}	t_token_type;

typedef struct s_cmd
{
	char 				**args;
	struct s_redirs	 		*redirs;
	// int					fd_in;
	// int					fd_out;
	// int					buitin_id;
	struct s_cmd		*next;
}	t_cmd;


typedef struct s_token
{
	t_token_type		type;
	char					*value;
	struct s_token			*next;
}	t_token;


typedef struct s_shell
{
	char		**env;
	/* future fields: exit_status, last_pid, jobs list, etc. */
}	t_shell;
#endif