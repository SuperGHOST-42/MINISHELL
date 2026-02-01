/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpereir <arpereir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:50:37 by hgutterr          #+#    #+#             */
/*   Updated: 2026/02/01 19:09:41 by arpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*parse(t_shell *shell, char *line)
{
	t_token	*tokens;
	t_cmd	*cmds;
	t_cmd	*current;

	(void)shell;
	if (ft_isempty(line))
		return (NULL);
	add_history(line);
	tokens = tokenization(line);
<<<<<<< HEAD
	if (syntax_check(tokens) == 1)
=======
	if (syntax_check(tokens) == 1) // syntax_check returns 1 on error
>>>>>>> ghost
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
<<<<<<< HEAD
		current = cmds;
		while (current)
		{
			if (current->args && current->args[0])
				current->builtin = get_builtin_type(current->args[0]);
			current = current->next;
		}
		return (cmds);
	}
	return (NULL);
}
=======
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
>>>>>>> ghost
