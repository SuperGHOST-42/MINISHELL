/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariclenes <ariclenes@student.42lisboa.com> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 15:20:00 by ariclenes         #+#    #+#             */
/*   Updated: 2026/03/08 15:20:00 by ariclenes        ###   ########.fr       */
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

static int	free_and_fail(char *res)
{
	free(res);
	return (1);
}

int	expand_word_value(t_shell *shell, char *word, char **expanded)
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
		if (word[i] == '$')
		{
			if (append_var(shell, word, &i, &res))
				return (free_and_fail(res));
			continue ;
		}
		buf[0] = word[i++];
		if (append_chunk(&res, buf))
			return (free_and_fail(res));
	}
	*expanded = res;
	return (0);
}
