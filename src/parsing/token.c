/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariclenes <ariclenes@student.42lisboa.com> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 15:20:00 by ariclenes         #+#    #+#             */
/*   Updated: 2026/03/08 15:20:00 by ariclenes        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/minishell_parse.h"

static void	set_quote_flags(t_token *tok, char quote, int preceded_by_space)
{
	tok->quoted = 1;
	tok->preceded_by_space = preceded_by_space;
	if (quote == '\'')
		tok->squoted = 1;
	else if (quote == '"')
		tok->dquoted = 1;
}

void	handle_word(t_token **tokens, char *line, int *i, int preceded_by_space)
{
	int		start;
	t_token	*tok;

	start = *i;
	while (line[*i] && !ft_isspace(line[*i]) && !ft_isoperator(line[*i])
		&& !ft_isquote(line[*i]))
		(*i)++;
	tok = new_token(WORD, ft_substr(line, start, *i - start));
	if (!tok)
		return ;
	tok->preceded_by_space = preceded_by_space;
	token_add_back(tokens, tok);
}

int	handle_quote(t_token **tokens, char *line, int *i, int preceded_by_space)
{
	char	quote;
	int		start;
	t_token	*tok;

	quote = line[*i];
	start = ++(*i);
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (line[*i] != quote)
		return (ft_putendl_fd("minishell: syntax error: unclosed quote", 2), 1);
	tok = new_token(WORD, ft_substr(line, start, *i - start));
	if (!tok)
		return (1);
	set_quote_flags(tok, quote, preceded_by_space);
	token_add_back(tokens, tok);
	(*i)++;
	return (0);
}

static t_token	*build_operator_token(char *line, int *i)
{
	if (line[*i] == '|')
		return (new_token(PIPE, ft_strdup("|")));
	if (line[*i] == '<' && line[*i + 1] == '<')
		return ((*i)++, new_token(R_HEREDOC, ft_strdup("<<")));
	if (line[*i] == '>' && line[*i + 1] == '>')
		return ((*i)++, new_token(R_APP, ft_strdup(">>")));
	if (line[*i] == '<')
		return (new_token(R_IN, ft_strdup("<")));
	if (line[*i] == '>')
		return (new_token(R_OUT, ft_strdup(">")));
	return (NULL);
}

void	handle_operator(t_token **tokens, char *line,
		int *i, int preceded_by_space)
{
	t_token	*tok;

	tok = build_operator_token(line, i);
	if (tok)
	{
		tok->preceded_by_space = preceded_by_space;
		token_add_back(tokens, tok);
	}
	(*i)++;
}
