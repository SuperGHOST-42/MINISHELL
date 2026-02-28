#include "../../includes/minishell.h"

static void	run_child(t_cmd *cmd, t_shell *shell);

void	exec_child(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		error_exit("fork");
	if (pid == 0)
	{
		setup_child_signals();
		run_child(cmd, shell);
	}
	setup_wait_signals();
	if (waitpid(pid, &status, 0) < 0)
	{
		perror("waitpid");
		setup_interactive_signals();
		shell->last_status = 1;
		return ;
	}
	setup_interactive_signals();
	shell->last_status = status_to_exit_code(status);
}

static void	run_child(t_cmd *cmd, t_shell *shell)
{
	if (!cmd)
		exit(1);
	if (apply_redirs(cmd->redirs))
		exit(1);
	if (!cmd->args || !cmd->args[0])
		exit(0);
	if (is_builtin(cmd))
		exit(exec_builtin(cmd, shell));
	exec_external_cmd(cmd, shell);
}
