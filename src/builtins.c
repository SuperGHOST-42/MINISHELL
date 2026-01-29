#include "../includes/minishell.h"

// Forward declarations
void	ft_echo(char *str);
void	ft_cd(char *path);
void	ft_pwd(void);
void	ft_export(char *key, char *value);
void	ft_unset(char *key);
void	ft_env(t_shell *shell);
void	ft_exit(t_shell *shell, char *exit_code_str);

t_builtin	get_builtin_type(const char *cmd)
{
	if (!cmd)
		return (BI_NONE);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (BI_ECHO);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (BI_CD);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (BI_PWD);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (BI_EXPORT);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (BI_UNSET);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (BI_ENV);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (BI_EXIT);
	return (BI_NONE);
}

int	execute_builtin(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (-1);
	
	if (cmd->builtin == BI_NONE)
		return (-1);
	
	if (cmd->builtin == BI_ECHO)
		ft_echo(cmd->args[1]);
	else if (cmd->builtin == BI_CD)
		ft_cd(cmd->args[1]);
	else if (cmd->builtin == BI_PWD)
		ft_pwd();
	else if (cmd->builtin == BI_EXPORT)
		ft_export(cmd->args[1], cmd->args[2]);
	else if (cmd->builtin == BI_UNSET)
		ft_unset(cmd->args[1]);
	else if (cmd->builtin == BI_ENV)
		ft_env(shell);
	else if (cmd->builtin == BI_EXIT)
		ft_exit(shell, cmd->args[1]);
	
	return (0);
}

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
	if (exit_code_str)
		exit_code = ft_atoi(exit_code_str);
	if (shell)
	{
		shell->should_exit = 1;
		shell->exit_code = exit_code;
	}
}
