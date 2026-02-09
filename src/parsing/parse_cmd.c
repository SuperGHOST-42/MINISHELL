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

// Append arg with quote tracking
int append_arg_with_quote(t_cmd *cmd, char *arg, int dquoted, int squoted)
{
	char			**new_args;
	t_arg_quote		**new_quote;
	t_arg_quote		*quote_info;
	int				count;
	int				i;

	count = 0;
	if (cmd->args)
	{
		while (cmd->args[count])
			count++;
	}
	new_args = malloc((count + 2) * sizeof(char *));
	if (!new_args)
		return (1);
	new_quote = malloc((count + 2) * sizeof(t_arg_quote *));
	if (!new_quote)
	{
		free(new_args);
		return (1);
	}
	i = 0;
	while (i < count)
	{
		new_args[i] = cmd->args[i];
		new_quote[i] = cmd->args_quote[i];
		i++;
	}
	new_args[i] = ft_strdup(arg);
	if (!new_args[i])
	{
		free(new_args);
		free(new_quote);
		return (1);
	}
	quote_info = malloc(sizeof(t_arg_quote));
	if (!quote_info)
	{
		free(new_args[i]);
		free(new_args);
		free(new_quote);
		return (1);
	}
	quote_info->dquoted = dquoted;
	quote_info->squoted = squoted;
	new_quote[i] = quote_info;
	new_args[i + 1] = NULL;
	new_quote[i + 1] = NULL;
	if (cmd->args)
		free(cmd->args);
	if (cmd->args_quote)
		free(cmd->args_quote);
	cmd->args = new_args;
	cmd->args_quote = new_quote;
	return (0);
}

static t_token	*process_word_sequence(t_cmd *cmd, t_token *tokens)
{
	char	*concat;
	char	*temp;
	int		has_dquote;
	int		has_squote;

	concat = NULL;
	has_dquote = 0;
	has_squote = 0;

	while (tokens && tokens->type == WORD)
	{
		// If this token was preceded by space and we already have a concat, 
		// finish the current argument and start a new one
		if (concat && tokens->preceded_by_space)
		{
			if (append_arg_with_quote(cmd, concat, has_dquote, has_squote))
			{
				free(concat);
				return (NULL);
			}
			free(concat);
			concat = NULL;
			has_dquote = 0;
			has_squote = 0;
		}
		
		// Concatenate this token with current or start new
		if (concat == NULL)
			concat = ft_strdup(tokens->value);
		else
		{
			temp = concat;
			concat = ft_strjoin(concat, tokens->value);
			free(temp);
			if (!concat)
				return (NULL);
		}
		if (tokens->dquoted)
			has_dquote = 1;
		if (tokens->squoted)
			has_squote = 1;
		tokens = tokens->next;
	}

	if (concat)
	{
		if (append_arg_with_quote(cmd, concat, has_dquote, has_squote))
		{
			free(concat);
			return (NULL);
		}
		free(concat);
	}
	return (tokens);
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
			tokens = process_word_sequence(cur, tokens);
			// process_word_sequence returns NULL when all WORD tokens consumed
			// This is OK - just continue to next iteration which will exit the loop
			continue ;
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
