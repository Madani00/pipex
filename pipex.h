/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:45:01 by eamchart          #+#    #+#             */
/*   Updated: 2025/02/02 16:05:17 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "Libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

void	free_args(char **arg);
void	free_all(char **args, char *p1);
void	waiting_process(int pid, int spid, int *pipefds);
int		check_spaces(char *str);
void	args_validate(int argc, char **av);
void	error_message(char *message, char *file);
char	*getenv_path(char **envp);
char	*get_path2(char *cmd, char **env);
void	check_dots(char **dots);

#endif
