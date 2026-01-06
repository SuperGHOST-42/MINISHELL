<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 14:11:50 by hgutterr          #+#    #+#             */
/*   Updated: 2026/01/06 12:20:36 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO:
// handle || && |(end) cases


#include "../includes/minishell.h"
#include <readline/readline.h>

<<<<<<< HEAD
const char *token_type_to_str(t_token_type type);

t_token *tokenization(char *line)
{
    int     i;
    t_token *tokens;

    i = 0;
    tokens = NULL;
    while (line[i])
    {
        if (ft_isspace(line[i]))
            i++;
        else if (ft_isquote(line[i]))
        {
            if (handle_quote(&tokens, line, &i))
            {
                free_tokens(tokens);
                return (NULL);
            }
        }
        else if (ft_isoperator(line[i]))
            handle_operator(&tokens, line, &i);
        else
            handle_word(&tokens, line, &i);
    }
    return (tokens);
}

void	accept_line(t_shell *shell, char *line)
{
	t_token *tokens;

	(void)shell; // currently not used
	if (ft_isempty(line))
		return ;
	add_history(line);
	printf("%s\n", line);
	tokens = tokenization(line);
	if (syntax_check(tokens) == 1) // syntax_check returns 1 on error
	{
		exit_shell(tokens, 2);
		return ;
	}

	if (!tokens)
		printf("No tokens generated.\n");
	else
	{
		t_token *tmp = tokens;
		while (tmp)
		{
			printf("TOKEN [%s] : \"%s\"\n", token_type_to_str(tmp->type), tmp->value);
			tmp = tmp->next;
		}
		// execute_simple_command(tokens, shell);
		free_tokens(tokens);
	}
}
void	minishell(t_shell *shell)
{
	char *line;
	while(1)
	{
		line = readline("$> ");
		if (!line)
		{
			rl_clear_history();
			exit(0);
		}
		accept_line(shell, line);
		free(line);
	}
=======
static void error_exit(const char *msg)
{
	perror(msg);
	exit(1);
}

char	*ft_getline(void)
{
	char cwd[BUFSIZ];
	char *buf;

	getcwd(cwd, sizeof(cwd));
	printf("%s", cwd);
	buf = readline(" $> ");
	return (buf);
>>>>>>> ghost
}

int	main(int argc, char **argv, char **env)
{
<<<<<<< HEAD
	t_shell shell;

	if(argc != 1)
		return (-1);
	(void)argv;
	(void)argc;
	shell.env = env;
	minishell(&shell);
}
///// DEBUG FUNCTION /////

const char *token_type_to_str(t_token_type type)
{
    if (type == WORD)
        return ("WORD");
    if (type == PIPE)
        return ("PIPE");
    if (type == R_IN)
        return ("R_IN");
    if (type == R_OUT)
        return ("R_OUT");
    if (type == R_HEREDOC)
        return ("R_HEREDOC");
    if (type == R_APP)
        return ("R_APP");
    return ("UNKNOWN");
=======
	char *line;
	
	while (1)
	{
		line = ft_getline();
		if (line == NULL)
			break;
		printf("%s\n", line);
		// do stuff
		free(line);
	}
>>>>>>> ghost
}
