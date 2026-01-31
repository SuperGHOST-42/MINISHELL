/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:50:14 by hgutterr          #+#    #+#             */
/*   Updated: 2026/01/30 18:50:14 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->type = type;
	tok->value = value;
	tok->next = NULL;
	return (tok);
}

void	token_add_back(t_token **lst, t_token *node)
{
	t_token	*tmp;

	if (!lst || !node)
		return;
	if (!*lst)
	{
		*lst = node;
		return;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

void	handle_word(t_token **tokens, char *line, int *i)
{
	int		start;
	t_token	*tok;

	start = *i;
	while (line[*i] && !ft_isspace(line[*i]) && !ft_isoperator(line[*i])
		&& !ft_isquote(line[*i]))
		(*i)++;
	tok = new_token(WORD, ft_substr(line, start, *i - start));
	if (!tok)
		return;
	token_add_back(tokens, tok);
}

int	handle_quote(t_token **tokens, char *line, int *i)
{
	char	quote;
	int		start;
	t_token	*tok;

	quote = line[*i];
	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (line[*i] != quote)
		return (1);
	tok = new_token(WORD, ft_substr(line, start, *i - start));
	if (!tok)
		return (1);
	token_add_back(tokens, tok);
	if (line[*i] == quote)
		(*i)++;
	return (0);
}

void	handle_operator(t_token **tokens, char *line, int *i)
{
	t_token	*tok;
	char	*op;

	tok = NULL;
	op = NULL;
	if (line[*i] == '|')
		op = "|";
	else if (line[*i] == '<' && line[*i + 1] == '<')
	{
		op = "<<";
		(*i)++;
	}
	else if (line[*i] == '>' && line[*i + 1] == '>')
	{
		op = ">>";
		(*i)++;
	}
	else if (line[*i] == '<')
		op = "<";
	else if (line[*i] == '>')
		op = ">";
	if (op)
	{
		if (line[*i] == '|')
			tok = new_token(PIPE, ft_strdup(op));
		else if (op[0] == '<' && op[1] == '<')
			tok = new_token(R_HEREDOC, ft_strdup(op));
		else if (op[0] == '>' && op[1] == '>')
			tok = new_token(R_APP, ft_strdup(op));
		else if (op[0] == '<')
			tok = new_token(R_IN, ft_strdup(op));
		else if (op[0] == '>')
			tok = new_token(R_OUT, ft_strdup(op));
		if (tok)
			token_add_back(tokens, tok);
	}
	(*i)++;
}
