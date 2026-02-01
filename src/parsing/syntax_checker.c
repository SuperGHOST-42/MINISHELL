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

#include "../includes/minishell.h"

static int	check_pipe(t_token *tokens)
{
	if (!tokens->next || tokens->next->type == PIPE)
	{
		printf("minishell: parse error near `|'\n");
		return (1);
	}
	return (0);
}

static int	check_redir(t_token *tokens)
{
	if (!tokens->next || tokens->next->type != WORD)
	{
		if (!tokens->next)
			printf("minishell: parse error near `newline'\n");
		else
			printf("minishell: parse error near `%s'\n", tokens->value);
		return (1);
	}
	return (0);
}

int	syntax_check(t_token *tokens)
{
	if (!tokens)
		return (1);
	if (tokens->type == PIPE)
	{
		printf("minishell: parse error near `|'\n");
		return (1);
	}
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
