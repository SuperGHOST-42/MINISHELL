#include "../../includes/minishell.h"

int	exec_builtin(t_cmd *cmd, t_shell *shell)
{
	if (!cmd)
		return (1);
	if (cmd->builtin == BI_PWD)
		ft_pwd();
	if (cmd->builtin == BI_ENV)
		ft_env(shell);
	if (cmd->builtin == BI_EXIT)
		ft_exit(shell, cmd->args[1]);
	if( cmd->builtin == BI_ECHO)
		ft_echo(cmd->args);
	return (0);
}