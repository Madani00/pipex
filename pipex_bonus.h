/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 22:16:11 by eamchart          #+#    #+#             */
/*   Updated: 2025/01/25 11:02:10 by eamchart         ###   ########.fr       */
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
void	waiting_process(int pid, int spid, int *pipefds);
int		check_spaces(char *str);
void	args_validate(int argc, char **av);
void	error_message(char *message, char *file);
char	*getenv_path(char **envp);

#endif
