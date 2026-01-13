/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 18:58:12 by hgutterr          #+#    #+#             */
/*   Updated: 2026/01/07 18:58:12 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			/* free previously allocated strings */
			while (i-- > 0)
				free(args[i]);
			free(args);
			return (NULL);
		}
		i++;
		tmp = tmp->next;
	}
	args[i] = NULL;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
	{
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

static t_redirs *new_redir(t_token_type type, char *target)
{
	t_redirs *r = malloc(sizeof(t_redirs));
	if (!r)
		return (NULL);
	r->type = type;
	r->target = ft_strdup(target);
	if (!r->target)
	{
		free(r);
		return (NULL);
	}
	r->expand = (type == R_HEREDOC) ? 0 : 1;
	r->heredoc_fd = -1;
	r->next = NULL;
	return (r);
}

int add_redir(t_redirs **list, t_token_type type, char *target)
{
	t_redirs *r;

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

int append_arg(t_cmd *cmd, char *arg)
{
	char **new_args;
	int i = 0;

	if (!cmd)
		return (1);
	while (cmd->args && cmd->args[i])
		i++;
	new_args = malloc((i + 2) * sizeof(char *));
	if (!new_args)
		return (1);
	for (int j = 0; j < i; j++)
		new_args[j] = cmd->args[j];
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

static t_cmd *new_cmd(void)
{
	t_cmd *cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->builtin = BI_NONE;
	cmd->pid = -1;
	cmd->next = NULL;
	return (cmd);
}

static void add_cmd(t_cmd **list, t_cmd *cmd)
{
	if (!list || !cmd)
		return;
	if (!*list)
	{
		*list = cmd;
		return;
	}
	cmd->next = *list;
	*list = cmd;
}

static void free_cmd(t_cmd *cmd)
{
	int i = 0;

	if (!cmd)
		return;
	if (cmd->args)
	{
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	while (cmd->redirs)
	{
		t_redirs *tmp = cmd->redirs;
		cmd->redirs = cmd->redirs->next;
		free(tmp->target);
		free(tmp);
	}
	free(cmd);
}

void free_cmds(t_cmd *cmds)
{
	while (cmds)
	{
		t_cmd *tmp = cmds;
		cmds = cmds->next;
		free_cmd(tmp);
	}
}

void print_cmds(t_cmd *cmds)
{
	while (cmds)
	{
		printf("CMD ARGS:");
		if (cmds->args)
		{
			int i = 0;
			while (cmds->args[i])
			{
				printf(" \"%s\"", cmds->args[i]);
				i++;
			}
		}
		printf("\n");
		if (cmds->redirs)
		{
			printf("REDIRS:");
			t_redirs *r = cmds->redirs;
			while (r)
			{
				const char *s = (r->type == R_IN) ? "<" : (r->type == R_OUT) ? ">" : (r->type == R_APP) ? ">>" : "<<";
				printf(" %s \"%s\"", s, r->target);
				r = r->next;
			}
			printf("\n");
		}
		cmds = cmds->next;
	}
}


t_cmd *parse_tokens_to_cmds(t_token *tokens)
{
	t_cmd *head = NULL;
	t_cmd *cur = NULL;

	while (tokens)
	{
		if (tokens->type == PIPE)
		{
			/* finish current command and prepare for next */
			cur = NULL;
			tokens = tokens->next;
			continue;
		}
		/* start a new command if needed */
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
			tokens = tokens->next;
		}
		else if (ft_isredir(tokens->type))
		{
			t_token_type type = tokens->type;
			tokens = tokens->next; /* syntax_check ensures this exists and is WORD */
			if (!tokens || tokens->type != WORD)
			{
				free_cmds(head);
				return (NULL);
			}
			if (add_redir(&cur->redirs, type, tokens->value))
			{
				free_cmds(head);
				return (NULL);
			}
			tokens = tokens->next;
		}
		else if (tokens->type == PIPE)
		{
			/* next iteration will handle creating next command */
			cur = NULL;
			tokens = tokens->next;
		}
		else
			tokens = tokens->next;
	}
	return (head);
}

void execute_simple_command(t_token *tokens, t_shell *shell)
{
	t_cmd *cmds = parse_tokens_to_cmds(tokens);
	if (!cmds)
	{
		printf("CMD ARGS: (parse/alloc error)\n");
		return;
	}
	print_cmds(cmds);
	free_cmds(cmds);
	(void)shell;
}