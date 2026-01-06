/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpereir <arpereir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 13:46:41 by hgutterr          #+#    #+#             */
/*   Updated: 2026/01/06 13:42:27 by arpereir         ###   ########.fr       */
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

typedef struct s_token
{
	t_token_type		type;
	char					*value;
	struct s_token			*next;
}	t_token;

typedef struct s_shell
{
	char		**env;
}	t_shell;






















































/*
typedef struct s_cmd
{
	char 				**args;
	struct s_redirs	 		*redirs;
	// int					fd_in;
	// int					fd_out;
	// int					buitin_id;
	struct s_cmd		*next;
}	t_cmd;
*/

#endif