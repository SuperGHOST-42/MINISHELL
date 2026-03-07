/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline_utils.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghost <ghost@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 20:20:00 by ghost             #+#    #+#             */
/*   Updated: 2026/02/19 20:20:00 by ghost            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_PIPELINE_UTILS_H
# define EXECUTE_PIPELINE_UTILS_H

# include "minishell.h"

int		pipe_prepare(int fd[2], int has_next);
void	close_fd(int fd);
int		dup_prepare(int fd[2], int prev_fd, int has_next);
void	refresh_fds(int *prev_read, int fd[2], int has_next);
pid_t	open_process(t_cmd *cur, t_shell *shell, int prev_read, int fd[2]);
void	wait_pipeline(t_cmd *cmd, t_shell *shell);

#endif
