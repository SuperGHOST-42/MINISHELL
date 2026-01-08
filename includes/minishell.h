#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>

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

#endif