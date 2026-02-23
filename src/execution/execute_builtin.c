#include "../../includes/minishell.h"

static void	restore_stdio(int saved_in, int saved_out)
{
	if (saved_in >= 0)
	{
		if (dup2(saved_in, STDIN_FILENO) < 0)
			perror("dup2");
		close(saved_in);
	}
	if (saved_out >= 0)
	{
		if (dup2(saved_out, STDOUT_FILENO) < 0)
			perror("dup2");
		close(saved_out);
	}
}

int	exec_builtin(t_cmd *cmd, t_shell *shell)
{
	if (!cmd)
		return (1);
	if (cmd->builtin == BI_CD)
		return (ft_cd(shell, cmd->args));
	if (cmd->builtin == BI_PWD)
		return (ft_pwd());
	if (cmd->builtin == BI_EXPORT)
		return (ft_export(shell, cmd->args));
	if (cmd->builtin == BI_UNSET)
		return (ft_unset(shell, cmd->args));
	if (cmd->builtin == BI_ENV)
		return (ft_env(shell, cmd->args));
	if (cmd->builtin == BI_EXIT)
		return (ft_exit(shell, cmd->args));
	if (cmd->builtin == BI_ECHO)
		return (ft_echo(cmd->args));
	return (0);
}

int	exec_builtin_parent(t_cmd *cmd, t_shell *shell)
{
	int	saved_in;
	int	saved_out;
	int	status;

	if (!cmd)
		return (1);
	saved_in = dup(STDIN_FILENO);
	if (saved_in < 0)
	{
		perror("dup");
		return (1);
	}
	saved_out = dup(STDOUT_FILENO);
	if (saved_out < 0)
	{
		close(saved_in);
		perror("dup");
		return (1);
	}
	if (apply_redirs(cmd->redirs))
		status = 1;
	else
		status = exec_builtin(cmd, shell);
	restore_stdio(saved_in, saved_out);
	return (status);
}
