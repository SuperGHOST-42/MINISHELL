#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

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
	char 		**envp;
	int			last_status;	// $? (0..255)
	int 		should_exit;	// flag to indicate if shell should exit
	int 		exit_code;		// exit code to use when exiting
}	t_shell;

//ghost
int		is_parent_needed(t_builtin bi);
int		exec_builtin(t_cmd *cmd, t_shell *shell);
int		status_to_exit_code(int status);

//helpers
void 	print_args(t_cmd *cmd);
void	free_cmd(t_cmd *cmd);
void 	error_exit(char *msg);
char	*ft_readline(void);

//env
char	*get_envp_value(char **envp, const char *key);
char	*resolve_path(char **envp, char *cmd);

//exec
void	create_process(t_cmd *cmd, t_shell *shell);
int		exec_pipeline(t_cmd *cmds, t_shell *shell);

//list helpers
int		stack_size(t_cmd *stack);
t_cmd	*ft_new_node(void);
void	ft_lstadd_front(t_cmd **list, t_cmd *new);
void	ft_lstadd_back(t_cmd **list, t_cmd *new);



#endif
