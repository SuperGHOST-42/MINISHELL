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

#include "../includes/minishell.h"

void	ft_echo(char *str)
{
	(void)str;
}

void	ft_cd(char *path)
{
	(void)path;
}

void	ft_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("getcwd() error");
}

void	ft_export(char *key, char *value)
{
	(void)key;
	(void)value;
}

void	ft_unset(char *key)
{
	(void)key;
}
