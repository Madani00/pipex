/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 22:16:11 by eamchart          #+#    #+#             */
/*   Updated: 2025/01/28 21:53:45 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "Libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define BUFFER_SIZE 1

void	free_args(char **arg);
void	free_all(char **args, char *p1);
void	waiting_process(int pid);
int		check_spaces(char *str);
void	args_validate(int argc, char **av);
void	error_message(char *message, char *file);
char	*getenv_path(char **envp);

char	*fetch_line(char *buffer);
char	*allocation(int fd);
char	*get_next_line(int fd);
int	check_spaces(char *str);
int apply_command(char *cmd, char **env, int in_fd, int out_fd);

#endif
