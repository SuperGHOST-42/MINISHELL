#include "../includes/minishell.h"

void ft_pwd(void)
{
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("getcwd() error");

}

void ft_env(t_shell *shell)
{
	t_env	*current;

	if (!shell || !shell->env)
		return ;
	current = shell->env;
	while (current)
	{
		if (current->has_value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

void	ft_exit(t_shell *shell, char *exit_code_str)
{
	int	exit_code;

	exit_code = 0;
	if (exit_code_str != 0)
		exit_code = ft_atoi(exit_code_str);
	if (shell)
	{
		shell->should_exit = 1;
		shell->exit_code = exit_code;
	}
	exit(exit_code);
}