/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpereir <arpereir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:48:26 by hgutterr          #+#    #+#             */
/*   Updated: 2026/01/28 22:28:38 by arpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/minishell_parse.h"

const char *token_type_to_str(t_token_type type);
void test(t_token *tokens);

t_cmd 	*parse(t_shell *shell, char *line)
{
	t_token *tokens;
	t_cmd *cmds;

	(void)shell; // currently not used
	if (ft_isempty(line))
		return (NULL);
	add_history(line);
	tokens = tokenization(line);
	if (syntax_check(tokens) == 1) // syntax_check returns 1 on error
	{
		exit_shell(tokens, 2);
		return (NULL);
	}
	if (!tokens)
		printf("No tokens generated.\n");
	else
	{
		cmds = parse_tokens_to_cmds(tokens);
		free_tokens(tokens);
		return (cmds);
	}
    return (NULL);
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