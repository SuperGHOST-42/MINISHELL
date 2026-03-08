/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_build.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariclenes <ariclenes@student.42lisboa.com> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 18:46:00 by ariclenes         #+#    #+#             */
/*   Updated: 2026/03/08 18:46:00 by ariclenes        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/minishell_parse.h"

int	parse_cmd_token(t_cmd *cmd, t_token **tokens);

static int	ensure_current_cmd(t_cmd **head, t_cmd **cur)
{
	*cur = new_cmd();
	if (!*cur)
		return (1);
	add_cmd(head, *cur);
	return (0);
}

t_cmd	*parse_tokens_to_cmds(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*cur;

	head = NULL;
	cur = NULL;
	while (tokens)
	{
		if (tokens->type == PIPE)
		{
			cur = NULL;
			tokens = tokens->next;
			continue ;
		}
		if (!cur && ensure_current_cmd(&head, &cur))
			break ;
		if (parse_cmd_token(cur, &tokens))
			break ;
	}
	if (tokens)
		free_cmds(head);
	if (tokens)
		return (NULL);
	return (head);
}
