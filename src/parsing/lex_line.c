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

t_cmd	*parse(t_shell *shell, char *line)
{
	t_token	*tokens;
	t_cmd	*cmds;

	if (ft_isempty(line))
		return (NULL);
	tokens = tokenization(line);
	if (!tokens)
		return (shell->last_status = 2, NULL);
	if (syntax_check(tokens))
		return (free_tokens(tokens), shell->last_status = 2, NULL);
	cmds = parse_tokens_to_cmds(tokens);
	free_tokens(tokens);
	set_builtin_flags(cmds);
	return (cmds);
}
