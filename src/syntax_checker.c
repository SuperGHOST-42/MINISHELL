/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 13:00:10 by hgutterr          #+#    #+#             */
/*   Updated: 2025/12/18 13:00:10 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int syntax_check(t_token *tokens)
{
	if (!tokens)
		return (1);
	if(tokens->type == PIPE)
	{
		printf("minishell: parse error near `|'\n");
		return (1);
	}
	while (tokens)
	{
		if (tokens->type == PIPE)
		{
			if (!tokens->next || tokens->next->type == PIPE)
			{
				printf("minishell: parse error near `|'\n");
				return (1);
			}
		}
		if (ft_isredir(tokens->type))
		{
			if (!tokens->next || tokens->next->type != WORD)
			{
				if (!tokens->next)
					printf("minishell: parse error near `newline'\n");
				else
					printf("minishell: parse error near `%s'\n", tokens->value);
				return (1);
			}
		}
		tokens = tokens->next;
	}
	return (0);
}

int ft_isredir(t_token_type type)
{
	return (type == R_IN || type == R_OUT || type == R_APP || type == R_HEREDOC);
}