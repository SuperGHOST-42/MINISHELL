/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:55:20 by hgutterr          #+#    #+#             */
/*   Updated: 2026/01/30 18:55:20 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/minishell_parse.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->args_quote = NULL;
	cmd->redirs = NULL;
	cmd->builtin = BI_NONE;
	cmd->pid = -1;
	cmd->next = NULL;
	return (cmd);
}

void	add_cmd(t_cmd **list, t_cmd *cmd)
{
	t_cmd	*tmp;

	if (!list || !cmd)
		return;
	if (!*list)
	{
		*list = cmd;
		return;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = cmd;
}

void	free_cmd(t_cmd *cmd)
{
	t_redirs	*tmp;
	int			i;

	if (!cmd)
		return;
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	if (cmd->args_quote)
	{
		i = 0;
		while (cmd->args_quote[i])
		{
			free(cmd->args_quote[i]);
			i++;
		}
		free(cmd->args_quote);
	}
	while (cmd->redirs)
	{
		tmp = cmd->redirs;
		cmd->redirs = cmd->redirs->next;
		free(tmp->target);
		free(tmp);
	}
	free(cmd);
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;

	while (cmds)
	{
		tmp = cmds;
		cmds = cmds->next;
		free_cmd(tmp);
	}
}
