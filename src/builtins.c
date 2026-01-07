#include "../includes/minishell.h"

void ft_echo(char *str)
{
	;
}

void ft_cd(char *path)
{
	;
}

void ft_pwd(void)
{
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("getcwd() error");

}

void ft_export(char *key, char *value)
{
	;
}

void ft_unset(char *key)
{
	;
}

void ft_env(t_shell *shell)
{
	;
}

// void ft_exit(t_shell *shell, int exit_code)
// {
// 	shell->should_exit = 1;
// 	shell->exit_code = exit_code;
// }
