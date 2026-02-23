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

static void	set_exit_value(int sign, unsigned long long num, long long *out)
{
	if (sign < 0 && num == (unsigned long long)LLONG_MAX + 1ULL)
		*out = LLONG_MIN;
	else
		*out = (long long)(num * sign);
}

static int	parse_exit_number(const char *s, long long *out)
{
	int					i;
	int					sign;
	unsigned long long	num;
	unsigned long long	limit;

	if (!parse_sign(s, &i, &sign))
		return (0);
	num = 0;
	limit = (unsigned long long)LLONG_MAX;
	if (sign < 0)
		limit = (unsigned long long)LLONG_MAX + 1ULL;
	while (ft_isdigit(s[i]))
	{
		if (num > (limit - (unsigned long long)(s[i] - '0')) / 10ULL)
			return (0);
		num = (num * 10ULL) + (unsigned long long)(s[i] - '0');
		i++;
	}
	if (s[i] != '\0')
		return (0);
	set_exit_value(sign, num, out);
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
		return (ft_putendl_fd("minishell: exit: too many arguments", 2), 1);
	return (set_shell_exit(shell, (unsigned char)code));
}
