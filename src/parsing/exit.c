/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpereir <arpereir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:50:46 by hgutterr          #+#    #+#             */
/*   Updated: 2026/02/01 19:09:33 by arpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exit_shell(t_token *tokens, int exit_code)
{
	free_tokens(tokens);
	printf("Exiting shell with code %d\n", exit_code);
	return (exit_code);
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
	}
}
