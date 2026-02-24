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

static int	append_chunk(char **dst, char *chunk)
{
	char	*tmp;

	tmp = ft_strjoin(*dst, chunk);
	if (!tmp)
		return (1);
	free(*dst);
	*dst = tmp;
	return (0);
}

static int	append_named_var(t_shell *shell, char *s, int *i, char **out)
{
	int		start;
	char	*name;
	char	*value;

	start = *i + 1;
	*i = start;
	while (ft_isalnum(s[*i]) || s[*i] == '_')
		(*i)++;
	name = ft_substr(s, start, *i - start);
	if (!name)
		return (1);
	value = get_env_exec(shell->env, name);
	free(name);
	if (!value)
		return (0);
	return (append_chunk(out, value));
}

static int	append_var(t_shell *shell, char *s, int *i, char **out)
{
	int		ret;
	char	*value;

	if (s[*i + 1] == '?')
	{
		value = ft_itoa(shell->last_status);
		*i += 2;
		if (!value)
			return (1);
		ret = append_chunk(out, value);
		free(value);
		return (ret);
	}
	if (!(ft_isalpha(s[*i + 1]) || s[*i + 1] == '_'))
	{
		(*i)++;
		return (append_chunk(out, "$"));
	}
	return (append_named_var(shell, s, i, out));
}

static int	expand_word(t_shell *shell, char *word, char **expanded)
{
	char	*res;
	char	buf[2];
	int		i;

	res = ft_strdup("");
	if (!res)
		return (1);
	i = 0;
	buf[1] = '\0';
	while (word[i])
	{
		if (word[i] == '$' && append_var(shell, word, &i, &res))
			return (free(res), 1);
		if (word[i] == '$')
			continue ;
		buf[0] = word[i++];
		if (append_chunk(&res, buf))
			return (free(res), 1);
	}
	*expanded = res;
	return (0);
}

int	expand_tokens(t_shell *shell, t_token *tokens)
{
	char	*new_value;

	while (tokens)
	{
		if (tokens->type == WORD && !tokens->squoted)
		{
			if (expand_word(shell, tokens->value, &new_value))
				return (1);
			free(tokens->value);
			tokens->value = new_value;
		}
		tokens = tokens->next;
	}
	return (0);
}
