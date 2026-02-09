#include "../../includes/minishell.h"

int	exec_builtin(t_cmd *cmd, t_shell *shell)
{
	if (!cmd)
		return (1);
	if (cmd->builtin == BI_PWD)
		return(ft_pwd());
	if (cmd->builtin == BI_ENV)
		return(ft_env(shell));
	if (cmd->builtin == BI_EXIT)
		return(ft_exit(shell, cmd->args[1]));
	if (cmd->builtin == BI_ECHO)
		return(ft_echo(cmd->args));
	return (0);
}