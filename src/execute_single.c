# include "../includes/minishell.h"

int	status_to_exit_code(int status)
{
	int	sig;

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		return (128 + sig);
	}
	return (1);
}

int	is_parent_needed(t_builtin bi)
{
	if (bi == BI_CD)
		return (1);
	if (bi == BI_EXIT)
		return (1);
	if (bi == BI_EXPORT)
		return (1);
	if (bi == BI_UNSET)
		return (1);
	return (0);
}

int exec_builtin(t_cmd *cmd)
{
	printf("exec_builtin executed\n");
	return (77);
}

