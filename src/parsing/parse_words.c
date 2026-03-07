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

static int	alloc_arg_arrays(char ***args, t_arg_quote ***quotes, int n)
{
	*args = malloc((n + 2) * sizeof(char *));
	*quotes = malloc((n + 2) * sizeof(t_arg_quote *));
	if (!*args || !*quotes)
	{
		free(*args);
		free(*quotes);
		return (1);
	}
	return (0);
}

static int	set_new_arg(char **args, t_arg_quote **quotes, int n,
		char *arg, t_arg_quote *src)
{
	t_arg_quote	*info;

	args[n] = ft_strdup(arg);
	info = malloc(sizeof(t_arg_quote));
	if (!args[n] || !info)
	{
		free(args[n]);
		free(info);
		return (1);
	}
	info->dquoted = src->dquoted;
	info->squoted = src->squoted;
	quotes[n] = info;
	args[n + 1] = NULL;
	quotes[n + 1] = NULL;
	return (0);
}

int	append_arg_with_quote(t_cmd *cmd, char *arg, int dquoted, int squoted)
{
	char		**args;
	t_arg_quote	**quotes;
	t_arg_quote	info;
	int			n;

	n = arg_count(cmd);
	if (alloc_arg_arrays(&args, &quotes, n))
		return (1);
	copy_old_args(cmd, args, quotes, n);
	info.dquoted = dquoted;
	info.squoted = squoted;
	if (set_new_arg(args, quotes, n, arg, &info))
	{
		free(args);
		free(quotes);
		return (1);
	}
	free(cmd->args);
	free(cmd->args_quote);
	cmd->args = args;
	cmd->args_quote = quotes;
	return (0);
}
