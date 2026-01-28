#include "../includes/minishell.h"
#include "../../includes/minishell_parse.h"

void	hardcode(t_cmd *cmd);
static void	exec_cmd(t_cmd *cmd, t_shell *shell);
static void	init_shell(t_shell *shell);

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		error_exit("malloc");
	
	ft_bzero(shell, sizeof(t_shell));

	shell->env = env_init(envp);
	if (!shell->env)
		error_exit("env_init");
	
	init_shell(shell);	
	
	free_env(shell->env);
	free(shell); // fazer: free_shell();
	
	return (shell->exit_code);
}

static void	init_shell(t_shell *shell)
{
	char	*line;
	t_cmd	*cmd;
	
	while (1)
	{
		line = ft_readline();
		if (line == NULL)
			break;
		else
			add_history(line);
		free(line);
		cmd = malloc(sizeof(t_cmd));
		if (!cmd)
			error_exit("malloc");
		ft_bzero(cmd, sizeof(t_cmd));
		//hardcode(cmd); //hugo
		
		cmd = parse(shell, line);
		print_cmds(cmd);
		
		//exec_cmd(cmd, shell);
		//free_cmds(cmd);
		if (shell->should_exit != 0)
			break ;
	}
}

static void	exec_cmd(t_cmd *cmd, t_shell *shell)
{
	if (cmd->next != NULL)
		exec_pipeline(cmd, shell);
	else if (is_builtin(cmd) && is_parent_needed(cmd))
		shell->last_status = exec_builtin(cmd, shell);
	else
		exec_child(cmd, shell);
	return ;
}

void	hardcode(t_cmd *cmd)
{
	t_cmd *cmd2;
	
	cmd2 = malloc(sizeof(t_cmd));
		if (!cmd2)
			error_exit("malloc");
	ft_bzero(cmd2, sizeof(t_cmd));

	//cmd2
	cmd2->args = malloc(sizeof(char *) * 3);
	if (!cmd2->args)
		error_exit("malloc");
	cmd2->args[0] = ft_strdup("wc");
	cmd2->args[1] = ft_strdup("-c");
	cmd2->args[2] = NULL;
	cmd2->builtin = BI_NONE;
	cmd2->pid = -1;
	cmd2->redirs = NULL;
	cmd2->next = NULL;

	//cmd
	cmd->args = malloc(sizeof(char *) * 3);
	if (!cmd->args)
		error_exit("malloc");
	cmd->args[0] = ft_strdup("echo");
	cmd->args[1] = ft_strdup("hello");
	cmd->args[2] = NULL;
	cmd->builtin = BI_NONE;
	cmd->pid = -1;
	cmd->redirs = NULL;
	cmd->next = cmd2;
}