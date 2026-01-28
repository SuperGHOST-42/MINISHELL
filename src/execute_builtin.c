#include "../includes/minishell.h"

int exec_builtin(t_cmd *cmd, t_shell *shell)
{
	if (cmd->builtin == BI_PWD)
		ft_pwd();
	else if (cmd->builtin == BI_ENV)
		ft_env(shell);
	else if (cmd->builtin == BI_EXIT)
		ft_exit(shell, cmd->args[1]);
	return (0);
}