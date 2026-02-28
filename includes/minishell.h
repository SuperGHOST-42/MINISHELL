/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpereir <arpereir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 11:58:35 by hgutterr          #+#    #+#             */
/*   Updated: 2026/02/23 17:12:22 by arpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>

typedef enum e_token_type
{
	WORD,
	PIPE,
	R_IN,
	R_OUT,
	R_APP,
	R_HEREDOC
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
	int						quoted;
	int						squoted;
	int						dquoted;
	int						preceded_by_space;
	struct s_token			*next;
}	t_token;

typedef struct s_arg_quote
{
	int						dquoted;
	int						squoted;
}	t_arg_quote;

typedef struct s_redirs
{
	t_token_type			type;
	char					*target;
	int						expand;
	int						heredoc_fd;
	struct s_redirs			*next;
}	t_redirs;

typedef struct s_cmd
{
	char 					**args;
	t_arg_quote				**args_quote;
	t_redirs		 		*redirs;
	t_builtin				builtin;
	pid_t					pid;
	struct s_cmd			*next;
}	t_cmd;	

typedef struct s_env
{
	char					*key;
	char					*value;
	int						has_value;
	struct s_env			*next;
}	t_env;

typedef struct s_shell
{
	t_env		*env;
	int			last_status;
	int 		should_exit;
	int 		exit_code;
}	t_shell;

int		is_parent_needed(t_cmd *cmd);
int		exec_builtin(t_cmd *cmd, t_shell *shell);
int		exec_builtin_parent(t_cmd *cmd, t_shell *shell);
int		status_to_exit_code(int status);
int		is_builtin(t_cmd *cmd);
char	**env_to_envp(t_env *env);
int		apply_redirs(t_redirs *redirs);
int		prepare_heredoc(t_cmd *cmds, t_shell *shell);
void	setup_interactive_signals(void);
void	setup_wait_signals(void);
void	setup_child_signals(void);
int		consume_sigint(void);

void 	error_exit(char *msg);
char	*ft_readline(void);

char	*resolve_path(t_env *env, char *cmd);

void	exec_child(t_cmd *cmd, t_shell *shell);
void	exec_pipeline(t_cmd *cmds, t_shell *shell);
void	exec_external_cmd(t_cmd *cmd, t_shell *shell);

int		ft_echo(char **args);
int		ft_cd(t_shell *shell, char **args);
int		ft_pwd(void);
int		ft_export(t_shell *shell, char **args);
int		ft_unset(t_shell *shell, char **args);
int		ft_env(t_shell *shell, char **args);
int		ft_exit(t_shell *shell, char **args);

t_env	*env_init_exec(char **envp);
char	*get_env_exec(t_env *env, const char *key);
void	free_env_exec(t_env *env);
void	free_envp(char **envp);

#endif
