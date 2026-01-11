# include "../includes/minishell.h"

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