/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghost <ghost@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 20:10:00 by ghost             #+#    #+#             */
/*   Updated: 2026/02/19 20:10:00 by ghost            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <limits.h>

static int	parse_sign(const char *s, int *i, int *sign)
{
	*i = 0;
	*sign = 1;
	if (s[*i] == '+' || s[*i] == '-')
	{
		if (s[*i] == '-')
			*sign = -1;
		(*i)++;
	}
	if (!ft_isdigit(s[*i]))
		return (0);
	return (1);
}

static int	append_digit(long long *value, int sign, int digit)
{
	if (sign > 0)
	{
		if (*value > (LLONG_MAX - digit) / 10)
			return (0);
		*value = (*value * 10) + digit;
	}
	else
	{
		if (*value < (LLONG_MIN + digit) / 10)
			return (0);
		*value = (*value * 10) - digit;
	}
	return (1);
}

static int	parse_exit_number(const char *s, long long *out)
{
	int			i;
	int			sign;
	long long	value;

	if (!parse_sign(s, &i, &sign))
		return (0);
	value = 0;
	while (ft_isdigit(s[i]))
	{
		if (!append_digit(&value, sign, s[i] - '0'))
			return (0);
		i++;
	}
	if (s[i] != '\0')
		return (0);
	*out = value;
	return (1);
}

static int	set_shell_exit(t_shell *shell, int code)
{
	shell->should_exit = 1;
	shell->exit_code = (unsigned char)code;
	return ((unsigned char)code);
}

int	ft_exit(t_shell *shell, char **args)
{
	long long	code;

	if (!shell)
		return (1);
	if (!args || !args[1])
		return (set_shell_exit(shell, shell->last_status));
	if (!parse_exit_number(args[1], &code))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		return (set_shell_exit(shell, 255));
	}
	if (args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	return (set_shell_exit(shell, (unsigned char)code));
}
