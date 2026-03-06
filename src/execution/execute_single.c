#include "../../includes/minishell.h"
#include "../../includes/minishell_parse.h"


int	run_child(t_cmd *cmd, t_shell *shell);

void	exec_child(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;
	int		r;

	pid = fork();
	if (pid < 0)
		error_exit("fork");
	if (pid == 0)
	{
		setup_child_signals();
		r = run_child(cmd, shell);
		free_cmds(cmd);
		free_env_exec(shell->env);
		free(shell);
		exit(r);
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

int	run_child(t_cmd *cmd, t_shell *shell)
{
	if (!cmd)
		return(1);
	if (apply_redirs(cmd->redirs))
		return(1);
	if (!cmd->args || !cmd->args[0])
		return(0);
	if (is_builtin(cmd))
		return(exec_builtin(cmd, shell));
	exec_external_cmd(cmd, shell);
	return(0);
}