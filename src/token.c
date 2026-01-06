/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 23:12:06 by hgutterr          #+#    #+#             */
/*   Updated: 2025/12/16 23:12:06 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token *new_token(t_token_type type, char *value)
{
	t_token *tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->type = type;
	tok->value = value;
	tok->next = NULL;
	return (tok);
}

void token_add_back(t_token **lst, t_token *new)
{
	t_token *tmp;

	if (!*lst)
	{
		*lst = new;
		return;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
void handle_word(t_token **tokens, char *line, int *i)
{
	int	start;

	start = *i;
	while (line[*i] && !ft_isspace(line[*i]) && !ft_isoperator(line[*i])
		&& !ft_isquote(line[*i]))
	(*i)++;
	token_add_back(tokens, new_token(WORD, ft_substr(line, start, *i- start)));
}
int handle_quote(t_token **tokens, char *line, int *i)
{
	char quote;
	int  start;

	quote = line[*i];
	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (line[*i] != quote)
		return (1);
	token_add_back(tokens,
		new_token(WORD, ft_substr(line, start, *i - start)));
	if (line[*i] == quote)
		(*i)++;
	return (0);
} 


void handle_operator(t_token **tokens, char *line, int *i)
{
	if (line[*i] == '|')
		token_add_back(tokens, new_token(PIPE, ft_strdup("|")));
	else if (line[*i] == '<' && line[*i + 1] == '<')
	{
		token_add_back(tokens, new_token(R_HEREDOC, ft_strdup("<<")));
		(*i)++;
	}
	else if (line[*i] == '>' && line[*i + 1] == '>')
	{
		token_add_back(tokens, new_token(R_APP, ft_strdup(">>")));
		(*i)++;
	}
	else if (line[*i] == '<')
		token_add_back(tokens, new_token(R_IN, ft_strdup("<")));
	else if (line[*i] == '>')
		token_add_back(tokens, new_token(R_OUT, ft_strdup(">")));
	(*i)++;
}
