/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:37:07 by eamchart          #+#    #+#             */
/*   Updated: 2025/02/01 16:46:01 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	check_limiter(char *line, char *limiter, int write_end)
{
	if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
	{
		free(line);
		close(write_end);
		exit(0);
	}
}

void	parent_doc(int read_end, int write_end)
{
	close(write_end);
	if (dup2(read_end, 0) == -1)
		ft_putstr_fd("Error dup2() failed:", 2);
	if (wait(NULL) == -1)
		ft_putstr_fd("Error wait() failed:", 2);
}

void	handle_doc(char *limiter, int *index)
{
	int		fds[2];
	pid_t	pid;
	char	*line;

	*index = 3;
	if (pipe(fds) == -1)
		ft_putstr_fd("Error pipe() failed:", 2);
	pid = fork();
	if (pid == -1)
		ft_putstr_fd("Error fork() failed:", 2);
	if (pid == 0)
	{
		close(fds[0]);
		line = get_next_line(0);
		while (line)
		{
			check_limiter(line, limiter, fds[1]);
			write(fds[1], line, ft_strlen(line));
			free(line);
			line = get_next_line(0);
		}
	}
	parent_doc(fds[0], fds[1]);
}
