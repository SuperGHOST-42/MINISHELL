#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <errno.h>
//hugo
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>

typedef enum e_token_type
{
	WORD,
	PIPE,
	R_IN, 			// <
	R_OUT,			// >
	R_APP,			// >>
	R_HEREDOC		// <<
}	t_token_type;

typedef enum e_builtin
{
	BI_NONE = 0,
	BI_ECHO,
	BI_CD,
	BI_PWD,
	BI_EXPORT,
	BI_UNSET,
	BI_ENV,
	BI_EXIT
}	t_builtin;

typedef struct s_token
{
	t_token_type			type;
	char					*value;
	int						quoted; // "" ''
	int						squoted; // ''
	int						dquoted; // ""
	struct s_token			*next;
}	t_token;

typedef struct s_redirs
{
	t_token_type			type;
	char					*target;
	int						expand; // HEREDOC expansion;
	int						heredoc_fd; // -1 if not heredoc
	struct s_redirs			*next;
}	t_redirs;

typedef struct s_cmd
{
	char 					**args;
	t_redirs		 		*redirs;
	t_builtin				builtin;
	pid_t					pid;
	struct s_cmd			*next;
}	t_cmd;	

typedef struct s_env
{
	char					*key; 		// "PATH"
	char					*value;		// "/usr/bin:/bin:..."
	int						has_value; 	// 1 if has value, 0 if just key
	struct s_env			*next;
}	t_env;

typedef struct s_shell
{
	t_env		*env;			// linked list of environment variables
	int			last_status;	// $? (0..255)
	int 		should_exit;	// flag to indicate if shell should exit
	int 		exit_code;		// exit code to use when exiting
}	t_shell;

//ghost
int		is_parent_needed(t_cmd *cmd);
int		exec_builtin(t_cmd *cmd, t_shell *shell);
int		status_to_exit_code(int status);
int		is_builtin(t_cmd *cmd);
char	**env_to_envp(t_env *env);

//helpers
void 	print_args(t_cmd *cmd);
void	free_tcmd(t_cmd *cmd);
void 	error_exit(char *msg);
char	*ft_readline(void);
void	ft_putstr(char *str);

//env
char	*get_envp_value(char **envp, const char *key);
char	*resolve_path(t_env *env, char *cmd);

//exec
void	exec_child(t_cmd *cmd, t_shell *shell);
void	exec_pipeline(t_cmd *cmds, t_shell *shell);

//list helpers
int		stack_size(t_cmd *stack);
t_cmd	*ft_new_node(void);
void	ft_lstadd_front(t_cmd **list, t_cmd *new);
void	ft_lstadd_back(t_cmd **list, t_cmd *new);
void	print_env_list(t_shell *shell);

//builtins
int		ft_pwd(void);
int		ft_env(t_shell *shell);
uint		ft_exit(t_shell *shell, char *exit_code_str);

//env
t_env	*env_init_exec(char **envp); //env.c
char	*get_env_exec(t_env *env, const char *key); //env.c
void	free_env_exec(t_env *env);
void	free_envp(char **envp);

#endif