/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:50:22 by hgutterr          #+#    #+#             */
/*   Updated: 2026/01/30 18:50:22 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/minishell_parse.h"

static int	parse_error(char *token)
{
	ft_putstr_fd("minishell: parse error near `", 2);
	ft_putstr_fd(token, 2);
	ft_putendl_fd("'", 2);
	return (1);
}

static int	check_pipe(t_token *tokens)
{
	if (!tokens->next || tokens->next->type == PIPE)
		return (parse_error("|"));
	return (0);
}

static int	check_redir(t_token *tokens)
{
	if (!tokens->next || tokens->next->type != WORD)
	{
		if (!tokens->next)
			return (parse_error("newline"));
		return (parse_error(tokens->next->value));
	}
	return (0);
}

int	syntax_check(t_token *tokens)
{
	if (!tokens)
		return (1);
	if (tokens->type == PIPE)
		return (parse_error("|"));
	while (tokens)
	{
		if (tokens->type == PIPE)
		{
			if (check_pipe(tokens))
				return (1);
		}
		if (ft_isredir(tokens->type))
		{
			if (check_redir(tokens))
				return (1);
		}
		tokens = tokens->next;
	}
	return (0);
}

int	ft_isredir(t_token_type type)
{
	if (type == R_IN || type == R_OUT)
		return (1);
	if (type == R_APP || type == R_HEREDOC)
		return (1);
	return (0);
}
