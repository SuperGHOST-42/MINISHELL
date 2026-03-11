/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpereir <arpereir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 15:05:00 by ariclenes         #+#    #+#             */
/*   Updated: 2026/03/11 01:57:46 by arpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/minishell_parse.h"

static char	**get_default_envp(void)
{
	char	**new_envp;
	char	cwd[BUFSIZ];
	char	*tmp;

	new_envp = malloc(4 * sizeof(char *));
	if (!new_envp)
		return (NULL);
	tmp = ft_strdup("PWD=");
	if (getcwd(cwd, sizeof(cwd)) == 0)
	{
		free(new_envp);
		return (NULL);
	}
	new_envp[0] = ft_strjoin(tmp, cwd);
	free(tmp);
	new_envp[1] = ft_strdup("SHLVL=0");
	new_envp[2] = ft_strdup("_=/usr/bin/env");
	new_envp[3] = NULL;
	return (new_envp);
}

static void	exec_cmd(t_cmd *cmd, t_shell *shell)
{
	int	hd_status;

	if (!cmd)
		return ;
	hd_status = prepare_heredoc(cmd, shell);
	if (hd_status)
	{
		shell->last_status = hd_status;
		return ;
	}
	if (cmd->next != NULL)
		exec_pipeline(cmd, shell);
	else if (is_builtin(cmd) && is_parent_needed(cmd))
		shell->last_status = exec_builtin_parent(cmd, shell);
	else
		exec_child(cmd, shell);
}

static void	handle_input_line(t_shell *shell, char *line)
{
	t_cmd	*cmd;

	if (*line == '\0')
	{
		free(line);
		return ;
	}
	add_history(line);
	cmd = parse(shell, line);
	free(line);
	if (!cmd)
		return ;
	shell->cmd_head = cmd;
	exec_cmd(cmd, shell);
	free_cmds(cmd);
	shell->cmd_head = NULL;
}

static void	init_shell(t_shell *shell)
{
	char	*line;
	int		interrupted;

	signals_prompt();
	while (!shell->should_exit)
	{
		line = ft_readline();
		interrupted = sigint_take();
		if (interrupted)
		{
			shell->last_status = 130;
			if (line && *line == '\0')
			{
				free(line);
				continue ;
			}
		}
		if (!line)
		{
			shell->should_exit = 1;
			shell->exit_code = shell->last_status;
			break ;
		}
		handle_input_line(shell, line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	int		exit_code;
	char	**new_envp;

	(void)argc;
	(void)argv;
	new_envp = get_default_envp();
	shell = malloc(sizeof(t_shell));
	if (!shell)
		error_exit("malloc");
	ft_bzero(shell, sizeof(t_shell));
	if (!envp[0])
		shell->env = envp_to_env(new_envp);
	else
		shell->env = envp_to_env(envp);
	free_split(new_envp);
	if (!shell->env)
		free(shell);
	init_shell(shell);
	exit_code = shell->exit_code;
	free_env(shell->env);
	free(shell);
	return (exit_code);
}
