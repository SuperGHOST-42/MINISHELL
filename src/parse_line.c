/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:48:26 by hgutterr          #+#    #+#             */
/*   Updated: 2026/01/06 16:06:26 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

const char *token_type_to_str(t_token_type type);
void test(t_token *tokens);

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
		test(tokens);
		// execute_simple_command(tokens, shell);
		free_tokens(tokens);
	}
}

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

void test(t_token *tokens)
{
	t_token *tmp = tokens;
	while (tmp)
	{
		printf("TOKEN [%s] : \"%s\"\n", token_type_to_str(tmp->type), tmp->value);
		tmp = tmp->next;
	}
}