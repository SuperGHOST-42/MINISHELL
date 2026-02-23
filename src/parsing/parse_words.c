/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghost <ghost@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 18:30:00 by ghost             #+#    #+#             */
/*   Updated: 2026/02/20 18:30:00 by ghost            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/minishell_parse.h"

static int	arg_count(t_cmd *cmd)
{
	int	n;

	n = 0;
	while (cmd->args && cmd->args[n])
		n++;
	return (n);
}

static void	copy_old_args(t_cmd *cmd, char **args, t_arg_quote **quotes, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		args[i] = cmd->args[i];
		quotes[i] = cmd->args_quote[i];
		i++;
	}
}

int	append_arg_with_quote(t_cmd *cmd, char *arg, int dquoted, int squoted)
{
	char		**args;
	t_arg_quote	**quotes;
	t_arg_quote	*info;
	int			n;

	n = arg_count(cmd);
	args = malloc((n + 2) * sizeof(char *));
	quotes = malloc((n + 2) * sizeof(t_arg_quote *));
	if (!args || !quotes)
		return (free(args), free(quotes), 1);
	copy_old_args(cmd, args, quotes, n);
	args[n] = ft_strdup(arg);
	info = malloc(sizeof(t_arg_quote));
	if (!args[n] || !info)
		return (free(args[n]), free(info), free(args), free(quotes), 1);
	info->dquoted = dquoted;
	info->squoted = squoted;
	quotes[n] = info;
	args[n + 1] = NULL;
	quotes[n + 1] = NULL;
	free(cmd->args);
	free(cmd->args_quote);
	return (cmd->args = args, cmd->args_quote = quotes, 0);
}

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

int	process_word_sequence(t_cmd *cmd, t_token **tokens)
{
	char	*concat = NULL;
	int		dquoted = 0;
	int		squoted = 0;
	while (*tokens && (*tokens)->type == WORD)
	{
		if (concat && (*tokens)->preceded_by_space)
		{
			if (append_arg_with_quote(cmd, concat, dquoted, squoted))
				return (free(concat), 1);
			free(concat);
			concat = NULL;
			dquoted = 0;
			squoted = 0;
		}
		if (append_piece(&concat, (*tokens)->value))
			return (free(concat), 1);
		dquoted |= (*tokens)->dquoted;
		squoted |= (*tokens)->squoted;
		*tokens = (*tokens)->next;
	}
	if (concat && append_arg_with_quote(cmd, concat, dquoted, squoted))
		return (free(concat), 1);
	return (free(concat), 0);
}
