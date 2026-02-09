/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_impl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:55:00 by hgutterr          #+#    #+#             */
/*   Updated: 2026/01/30 18:55:00 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(char **args)
{
	int i;
	int print_newline;

	if (!args || !args[0])
	{
		printf("\n");
		return (1);
	}
	i = 1;
	print_newline = 1;
	while (args[i] && args[i][0] == '-' && args[i][1])
	{
		int j = 1;
		int all_n = 1;

		while (args[i][j])
		{
			if (args[i][j] != 'n')
			{
				all_n = 0;
				break ;
			}
			j++;
		}
		if (!all_n)
			break ;
		print_newline = 0;
		i++;
	}
	while (args[i])
	{
		if (i > 1)
			printf(" ");
		printf("%s", args[i]);
		i++;
	}
	if (print_newline)
		printf("\n");
	return (0);
}

int	ft_cd(char *path)
{
	(void)path;
	return (0);
}

int	ft_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
	{
		perror("getcwd() error");
		return (1);
	}
	return (0);
}

int	ft_export(char *key, char *value)
{
	(void)key;
	(void)value;
	return (0);
}

int	ft_unset(char *key)
{
	(void)key;
	return (0);
}
