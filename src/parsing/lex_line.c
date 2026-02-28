/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:50:37 by hgutterr          #+#    #+#             */
/*   Updated: 2026/02/09 18:52:30 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/minishell_parse.h"

static void	set_builtin_flags(t_cmd *cmds)
{
	while (cmds)
	{
		if (cmds->args && cmds->args[0])
			cmds->builtin = get_builtin_type(cmds->args[0]);
		cmds = cmds->next;
	}
}

static t_cmd	*parse_fail(t_shell *shell, t_token *tokens, int status)
{
	if (tokens)
		free_tokens(tokens);
	shell->last_status = status;
	return (NULL);
}

t_cmd	*parse(t_shell *shell, char *line)
{
	t_token	*tokens;
	t_cmd	*cmds;

	if (ft_isempty(line))
		return (NULL);
	tokens = tokenization(line);
	if (!tokens)
		return (parse_fail(shell, NULL, 2));
	if (syntax_check(tokens))
		return (parse_fail(shell, tokens, 2));
	if (expand_tokens(shell, tokens))
		return (parse_fail(shell, tokens, 1));
	cmds = parse_tokens_to_cmds(tokens);
	free_tokens(tokens);
	set_builtin_flags(cmds);
	return (cmds);
}
