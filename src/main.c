/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 14:11:50 by hgutterr          #+#    #+#             */
/*   Updated: 2025/12/18 14:27:40 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO:
// handle || && |(end) cases


#include "../includes/minishell.h"

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
            handle_quote(&tokens, line, &i); // send address of i to modify it and continue from there 🤓
        else if (ft_isoperator(line[i]))
            handle_operator(&tokens, line, &i);
        else
            handle_word(&tokens, line, &i);
    }
    return (tokens);
}

void	accept_line(char *line)
{
t_token *tokens;

	if (ft_isempty(line))
		return ;
	add_history(line);

	printf("%s\n", line);
	
	tokens = tokenization(line);
	if (syntax_check(tokens) == 1) // syntax_check returns 1 on error
	{
		// TODO: free tokens
		return ;
	}

	if (!tokens)
		printf("No tokens generated.\n");
	else
	{
	    while (tokens)
	    {
			printf("TOKEN [%s] : \"%s\"\n", token_type_to_str(tokens->type), tokens->value);
			tokens = tokens->next;
		}
	}
}
void	minishell(char **env)
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
		accept_line(line);
		free(line);
	}
}

int	main(int argc, char **argv, char **env)
{
	if(argc != 1)
		return (-1);
	(void)argv;
	(void)argc;
	minishell(env);
	return (0);
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
}
