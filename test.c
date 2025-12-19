/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 14:11:50 by hgutterr          #+#    #+#             */
/*   Updated: 2025/12/19 12:48:00 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"


int	main(int argc, char **argv, char **env)
{
	if(argc != 1)
		return (-1);
	(void)argv;
	(void)argc;
	for (int i = 0; env[i]; i++)
		printf("%s\n\n\n", env[i]);
	return (0);
}
