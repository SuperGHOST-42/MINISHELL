/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpereir <arpereir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 19:30:00 by ghost             #+#    #+#             */
/*   Updated: 2026/02/24 15:01:00 by arpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/minishell_parse.h"

int			expand_word_value(t_shell *shell, char *word,
				char **expanded);

static int	is_heredoc_delim_token(t_token *tok, int *in_delim)
{
	if (*in_delim && tok->type == WORD)
	{
		if (!tok->next || tok->next->type != WORD
			|| tok->next->preceded_by_space)
			*in_delim = 0;
		return (1);
	}
	if (tok->type == R_HEREDOC)
	{
		*in_delim = 1;
		return (1);
	}
	*in_delim = 0;
	return (0);
}

int	expand_tokens(t_shell *shell, t_token *tokens)
{
	char	*new_value;
	int		in_delim;

	in_delim = 0;
	while (tokens)
	{
		if (is_heredoc_delim_token(tokens, &in_delim))
		{
			tokens = tokens->next;
			continue ;
		}
		if (tokens->type == WORD && !tokens->squoted)
		{
			if (expand_word_value(shell, tokens->value, &new_value))
				return (1);
			free(tokens->value);
			tokens->value = new_value;
		}
		tokens = tokens->next;
	}
	return (0);
}
