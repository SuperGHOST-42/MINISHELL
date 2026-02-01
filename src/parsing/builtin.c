/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpereir <arpereir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:49:52 by hgutterr          #+#    #+#             */
/*   Updated: 2026/02/01 21:27:11 by arpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/minishell_parse.h"

t_builtin	get_builtin_type(const char *cmd)
{
	if (!cmd)
		return (BI_NONE);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (BI_ECHO);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (BI_CD);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (BI_PWD);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (BI_EXPORT);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (BI_UNSET);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (BI_ENV);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (BI_EXIT);
	return (BI_NONE);
}
