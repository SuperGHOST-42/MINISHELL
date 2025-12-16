/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_macros.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 13:46:45 by hgutterr          #+#    #+#             */
/*   Updated: 2025/12/16 14:11:36 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_MACROS_H
# define MINISHELL_MACROS_H

# include "minishell.h"

typedef enum e_rtype
{
	R_IN, 			// <
	R_OUT,			// >
	R_APP,			// >>
	R_HEREDOC		// <<
} t_rtype;

#endif