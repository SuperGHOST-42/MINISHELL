/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 13:46:41 by hgutterr          #+#    #+#             */
/*   Updated: 2025/12/16 15:11:27 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H

# include "minishell.h"

typedef struct s_cmd
{
	char 				**args;
	t_redirs	 		*redirs;
	// int					fd_in;
	// int					fd_out;
	// int					buitin_id;
	struct s_cmd		*next;
}	t_cmd;

typedef struct s_redirs
{
	t_rtype				*type;
	char				*target;
}	t_redirs;


#endif