/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:50:27 by hgutterr          #+#    #+#             */
/*   Updated: 2026/02/09 18:52:30 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/minishell_parse.h"

static t_redirs	*new_redir(t_token_type type, char *target)
{
	t_redirs	*r;

	r = malloc(sizeof(t_redirs));
	if (!r)
		return (NULL);
	r->type = type;
	r->target = ft_strdup(target);
	if (!r->target)
	{
		free(r);
		return (NULL);
	}
	if (type == R_HEREDOC)
		r->expand = 0;
	else
		r->expand = 1;
	r->heredoc_fd = -1;
	r->next = NULL;
	return (r);
}

int	add_redir(t_redirs **list, t_token_type type, char *target)
{
	t_redirs	*r;
	t_redirs	*cur;

	if (!list || !target)
		return (1);
	r = new_redir(type, target);
	if (!r)
		return (1);
	if (!*list)
	{
		*list = r;
		return (0);
	}
	cur = *list;
	while (cur->next)
		cur = cur->next;
	cur->next = r;
	return (0);
}

static int	read_redir_target(t_token **tokens, char **target)
{
	char	*joined;
	char	*tmp;

	if (!*tokens || (*tokens)->type != WORD)
		return (1);
	joined = ft_strdup((*tokens)->value);
	if (!joined)
		return (1);
	*tokens = (*tokens)->next;
	while (*tokens && (*tokens)->type == WORD && !(*tokens)->preceded_by_space)
	{
		tmp = joined;
		joined = ft_strjoin(tmp, (*tokens)->value);
		free(tmp);
		if (!joined)
			return (1);
		*tokens = (*tokens)->next;
	}
	*target = joined;
	return (0);
}

static int	parse_token(t_cmd *cmd, t_token **tokens)
{
	char			*target;
	t_token_type	type;

	if ((*tokens)->type == WORD)
		return (process_word_sequence(cmd, tokens));
	if (!ft_isredir((*tokens)->type))
	{
		*tokens = (*tokens)->next;
		return (0);
	}
	type = (*tokens)->type;
	*tokens = (*tokens)->next;
	if (read_redir_target(tokens, &target))
		return (1);
	if (add_redir(&cmd->redirs, type, target))
		return (free(target), 1);
	free(target);
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
		if (!cur)
		{
			cur = new_cmd();
			if (!cur)
				return (free_cmds(head), NULL);
			add_cmd(&head, cur);
		}
		if (parse_token(cur, &tokens))
			return (free_cmds(head), NULL);
	}
	return (head);
}
