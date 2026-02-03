/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpereir <arpereir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:50:27 by hgutterr          #+#    #+#             */
/*   Updated: 2026/02/01 19:37:17 by arpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/minishell_parse.h"

int append_arg(t_cmd *cmd, char *arg)
{
	char**new_args;
	int	count;
	int	i;

	count = 0;
	if (cmd->args)
	{
		while (cmd->args[count])
		count++;
	}
	new_args = malloc((count + 2) * sizeof(char *));
	if (!new_args)
		return (1);
	i = 0;
	while (i < count)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[i] = ft_strdup(arg);
	if (!new_args[i])
	{
		free(new_args);
		return (1);
	}
	new_args[i + 1] = NULL;
	if (cmd->args)
		free(cmd->args);
	cmd->args = new_args;
	return (0);
}

static char	**create_args_from_tokens(t_token *tokens, int count)
{
	char	**args;
	int		i;
	t_token	*tmp;

	args = malloc((count + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	tmp = tokens;
	while (tmp && tmp->type == WORD)
	{
		args[i] = ft_strdup(tmp->value);
		if (!args[i])
		{
			while (i-- > 0)
				free(args[i]);
			free(args);
			return (NULL);
		}
		i++;
		tmp = tmp->next;
	}
	args[i] = NULL;
	return (args);
}

t_cmd	*create_cmd_from_tokens(t_token *tokens)
{
	int		count;
	t_token	*tmp;
	char	**args;
	t_cmd	*cmd;
	int		i;

	count = 0;
	tmp = tokens;
	while (tmp && tmp->type == WORD)
	{
		count++;
		tmp = tmp->next;
	}
	args = create_args_from_tokens(tokens, count);
	if (!args)
		return (NULL);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
	{
		i = count;
		while (i-- > 0)
			free(args[i]);
		free(args);
		return (NULL);
	}
	cmd->args = args;
	cmd->redirs = NULL;
	cmd->builtin = BI_NONE;
	cmd->pid = -1;
	cmd->next = NULL;
	return (cmd);
}

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
	r->next = *list;
	*list = r;
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
			{
				free_cmds(head);
				return (NULL);
			}
			add_cmd(&head, cur);
		}
		if (tokens->type == WORD)
		{
			if (append_arg(cur, tokens->value))
			{
				free_cmds(head);
				return (NULL);
			}
		}
		if (ft_isredir(tokens->type))
		{
			if (add_redir(&cur->redirs, tokens->type, tokens->next->value))
			{
				free_cmds(head);
				return (NULL);
			}
			tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	return (head);
}
