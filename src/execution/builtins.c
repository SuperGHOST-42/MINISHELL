#include "../../includes/minishell.h"

int	ft_pwd(void)
{
	char	cwd[BUFSIZ];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		return (0);
	}
	perror("getcwd");
	return (1);
}

int	ft_env(t_shell *shell)
{
	t_env	*current;

	if (!shell || !shell->env)
		return (0);
	current = shell->env;
	while (current)
	{
		if (current->key && current->has_value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (0);
}

int	ft_exit(t_shell *shell, char *exit_code_str)
{
	int	exit_code;

	if (!shell)
		return (1);
	if (!exit_code_str)
		exit_code = shell->last_status;
	else
		exit_code = ft_atoi(exit_code_str);
	shell->should_exit = 1;
	shell->exit_code = exit_code;
	return (exit_code);
}