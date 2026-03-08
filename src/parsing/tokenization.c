/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariclenes <ariclenes@student.42lisboa.com> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 15:20:00 by ariclenes         #+#    #+#             */
/*   Updated: 2026/03/08 15:20:00 by ariclenes        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/minishell_parse.h"

static int	read_one_token(t_token **tokens, char *line, int *i, int *had_space)
{
	if (ft_isquote(line[*i]))
	{
		if (handle_quote(tokens, line, i, *had_space))
			return (1);
	}
	else if (ft_isoperator(line[*i]))
		handle_operator(tokens, line, i, *had_space);
	else
		handle_word(tokens, line, i, *had_space);
	*had_space = 0;
	return (0);
}

t_token	*tokenization(char *line)
{
	t_token	*tokens;
	int		i;
	int		had_space;

	if (!line)
		return (NULL);
	tokens = NULL;
	i = 0;
	had_space = 1;
	while (line[i])
	{
		if (ft_isspace(line[i]))
		{
			had_space = 1;
			i++;
			continue ;
		}
		if (read_one_token(&tokens, line, &i, &had_space))
		{
			free_tokens(tokens);
			return (NULL);
		}
	}
	return (tokens);
}
