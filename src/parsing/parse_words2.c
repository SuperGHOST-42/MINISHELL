/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_words2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghost <ghost@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 20:00:00 by ghost             #+#    #+#             */
/*   Updated: 2026/02/26 20:00:00 by ghost            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/minishell_parse.h"

static int	append_piece(char **concat, char *value)
{
	char	*tmp;

	if (!*concat)
	{
		*concat = ft_strdup(value);
		return (!*concat);
	}
	tmp = *concat;
	*concat = ft_strjoin(tmp, value);
	free(tmp);
	return (!*concat);
}

static int	flush_concat(t_cmd *cmd, char **concat, int *dquoted, int *squoted)
{
	if (!*concat)
		return (0);
	if (append_arg_with_quote(cmd, *concat, *dquoted, *squoted))
	{
		free(*concat);
		return (1);
	}
	free(*concat);
	*concat = NULL;
	*dquoted = 0;
	*squoted = 0;
	return (0);
}

static int	handle_word_piece(t_token *token, char **concat)
{
	if (!(token->value[0] || token->quoted))
		return (0);
	if (append_piece(concat, token->value))
	{
		free(*concat);
		return (1);
	}
	return (0);
}

int	process_word_sequence(t_cmd *cmd, t_token **tokens)
{
	char	*concat;
	int		dquoted;
	int		squoted;

	concat = NULL;
	dquoted = 0;
	squoted = 0;
	while (*tokens && (*tokens)->type == WORD)
	{
		if ((*tokens)->preceded_by_space && flush_concat(cmd, &concat,
					&dquoted, &squoted))
			return (1);
		if (handle_word_piece(*tokens, &concat))
			return (1);
		dquoted |= (*tokens)->dquoted;
		squoted |= (*tokens)->squoted;
		*tokens = (*tokens)->next;
	}
	return (flush_concat(cmd, &concat, &dquoted, &squoted));
}
