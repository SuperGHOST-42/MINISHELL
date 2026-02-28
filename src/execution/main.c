#include "../../includes/minishell.h"
#include "../../includes/minishell_parse.h"

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
	exec_cmd(cmd, shell);
	free_cmds(cmd);
}

static void	init_shell(t_shell *shell)
{
	char	*line;

	setup_interactive_signals();
	while (!shell->should_exit)
	{
		line = ft_readline();
		if (consume_sigint())
		{
			shell->last_status = 130;
			free(line);
			continue ;
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

	(void)argc;
	(void)argv;
	if (!envp)
		error_exit("envp");
	shell = malloc(sizeof(t_shell));
	if (!shell)
		error_exit("malloc");
	ft_bzero(shell, sizeof(t_shell));
	shell->env = env_init_exec(envp);
	if (!shell->env)
	{
		free(shell);
		error_exit("env_init");
	}
	init_shell(shell);
	exit_code = shell->exit_code;
	free_env_exec(shell->env);
	free(shell);
	return (exit_code);
}
