#include "../../includes/minishell.h"
#include "../../includes/minishell_parse.h"

static void	exec_cmd(t_cmd *cmd, t_shell *shell)
{
	if (!cmd)
		return ;
	if (cmd->next != NULL)
		exec_pipeline(cmd, shell);
	else if (is_builtin(cmd) && is_parent_needed(cmd))
		shell->last_status = exec_builtin_parent(cmd, shell);
	else
		exec_child(cmd, shell);
}

static void	init_shell(t_shell *shell)
{
	char	*line;
	t_cmd	*cmd;

	while (!shell->should_exit)
	{
		line = ft_readline();
		if (!line)
		{
			shell->should_exit = 1;
			shell->exit_code = shell->last_status;
			break ;
		}
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		add_history(line);
		cmd = parse(shell, line);
		free(line);
		if (!cmd)
			continue ;
		exec_cmd(cmd, shell);
		free_cmds(cmd);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	int		exit_code;

	(void)argc;
	(void)argv;
	shell = malloc(sizeof(t_shell));
	if (!shell)
		error_exit("malloc");
	ft_bzero(shell, sizeof(t_shell));
	shell->env = env_init_exec(envp);
	if (!shell->env)
		error_exit("env_init");
	init_shell(shell);
	exit_code = shell->exit_code;
	free_env_exec(shell->env);
	free(shell);
	return (exit_code);
}
