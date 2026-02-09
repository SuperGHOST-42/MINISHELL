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

t_cmd	*parse(t_shell *shell, char *line)
{
	t_token	*tokens;
	t_cmd	*cmds;
	t_cmd	*current;

	(void)shell;
	if (ft_isempty(line))
		return (NULL);
	//add_history(line);
	tokens = tokenization(line);
	if (syntax_check(tokens) == 1)
	{
		exit_shell(tokens, 2);
		return (NULL);
	}
	if (!tokens)
		return (NULL);
	else
	{
		cmds = parse_tokens_to_cmds(tokens);
		free_tokens(tokens);
		current = cmds;
		while (current)
		{
			if (current->args && current->args[0])
				current->builtin = get_builtin_type(current->args[0]);
			current = current->next;
		}
		return (cmds);
	}
	return (NULL);
}
