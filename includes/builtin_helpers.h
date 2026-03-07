/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_helpers.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghost <ghost@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 20:10:00 by ghost             #+#    #+#             */
/*   Updated: 2026/02/19 20:10:00 by ghost            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_HELPERS_H
# define BUILTIN_HELPERS_H

# include "minishell.h"

int		bt_is_valid_key(const char *s);
int		bt_is_valid_export(const char *s);
int		bt_print_id_error(char *name, char *arg);
int		bt_key_match(const char *a, const char *b);
t_env	*bt_find_env(t_env *env, const char *key);
t_env	*bt_new_env_node(const char *key, const char *value, int has_value);
int		bt_append_env(t_env **env, t_env *new);
int		bt_set_env_value(t_env **env, const char *key, const char *value);
int		bt_ensure_env_key(t_env **env, const char *key);
void	bt_remove_env_key(t_env **env, const char *key);

#endif
