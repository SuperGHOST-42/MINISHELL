/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpereir <arpereir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:55:00 by hgutterr          #+#    #+#             */
/*   Updated: 2026/02/26 14:21:16 by arpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin_helpers.h"
#include <limits.h>

static int	is_echo_n(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || !arg[1])
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	cd_change_dir(t_shell *shell, char *path)
{
	char	oldpwd[PATH_MAX];
	char	cwd[PATH_MAX];

	oldpwd[0] = '\0';
	if (getcwd(oldpwd, sizeof(oldpwd)) == NULL)
		oldpwd[0] = '\0';
	if (chdir(path) < 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	if (oldpwd[0] && bt_set_env_value(&shell->env, "OLDPWD", oldpwd))
		return (1);
	if (getcwd(cwd, sizeof(cwd)) && bt_set_env_value(&shell->env, "PWD", cwd))
		return (1);
	return (0);
}

int	ft_echo(char **args)
{
	int	i;
	int	nl;

	if (!args || !args[0])
		return (printf("\n"), 0);
	i = 1;
	nl = 1;
	while (args[i] && is_echo_n(args[i]))
	{
		nl = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (nl)
		printf("\n");
	return (0);
}

int	ft_cd(t_shell *shell, char **args)
{
	char	*path;

	if (!shell || !args)
		return (1);
	if (args[1] && args[2])
	{
		//return (ft_putendl_fd("minishell: cd: too many arguments", 2), 0);
		return (ft_putendl_fd("", 2), 0);
	}
	path = args[1];
	if (!path)
		path = get_env_exec(shell->env, "HOME");
	if (!path)
		return (ft_putendl_fd("minishell: cd: HOME not set", 2), 1);
	return (cd_change_dir(shell, path));
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
