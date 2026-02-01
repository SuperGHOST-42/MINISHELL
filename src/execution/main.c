#include "../../includes/minishell.h"
#include "../../includes/minishell_parse.h"

static void	exec_cmd(t_cmd *cmd, t_shell *shell);
static void	init_shell(t_shell *shell);

static void print_cmds(t_cmd *cmds)
{
	while (cmds)
	{
		printf("CMD ARGS:");
		if (cmds->args)
		{
			int i = 0;
			while (cmds->args[i])
			{
				printf(" \"%s\"", cmds->args[i]);
				i++;
			}
		}
		printf("\n");
		if (cmds->redirs)
		{
			printf("REDIRS:");
			t_redirs *r = cmds->redirs;
			while (r)
			{
				const char *s = (r->type == R_IN) ? "<" : (r->type == R_OUT) ? ">" : (r->type == R_APP) ? ">>" : "<<";
				printf(" %s \"%s\"", s, r->target);
				r = r->next;
			}
			printf("\n");
		}
		printf("builtin = %i\n", cmds->builtin);
		cmds = cmds->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		error_exit("malloc");
	
	ft_bzero(shell, sizeof(t_shell));

	shell->env = env_init_exec(envp);
	if (!shell->env)
		error_exit("env_init");
	
	init_shell(shell);	
	
	free_env_exec(shell->env);
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
		cmd = malloc(sizeof(t_cmd));
		if (!cmd)
			error_exit("malloc");
		ft_bzero(cmd, sizeof(t_cmd));
		//hardcode(cmd); //hugo
		
		cmd = parse(shell, line);
		free(line);
		print_cmds(cmd);
		
		//exec_cmd(cmd, shell);
		free_cmds(cmd);
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