/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariclenes <ariclenes@student.42lisboa.com> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 18:00:00 by ariclenes         #+#    #+#             */
/*   Updated: 2026/03/08 18:00:00 by ariclenes        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static volatile sig_atomic_t	*sigint_state(void)
{
	static volatile sig_atomic_t	sigint_flag;

	return ((volatile sig_atomic_t *)&sigint_flag);
}

void	set_sigint_flag(void)
{
	*sigint_state() = 1;
}

int	consume_sigint(void)
{
	volatile sig_atomic_t	*sigint_flag;

	sigint_flag = sigint_state();
	if (!*sigint_flag)
		return (0);
	*sigint_flag = 0;
	return (1);
}
