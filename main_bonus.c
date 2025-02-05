/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 21:29:13 by eamchart          #+#    #+#             */
/*   Updated: 2025/02/02 16:30:05 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	open_file(char *file1, int *index)
{
	int	read_fd;

	*index = 2;
	read_fd = open(file1, O_RDONLY);
	if (read_fd == -1)
		error_message(" : No such file or directory", file1);
	dup2(read_fd, 0);
}

void	last_cmd(char *cmd, char **env, char *last_file, int pick_file)
{
	pid_t	pid;
	int		exit_cmd;
	int		out_fd;

	out_fd = openlast_file(pick_file, last_file);
	pid = fork();
	if (pid == -1)
		error_message("Error fork() failed:", 0);
	if (pid == 0)
	{
		if (dup2(out_fd, STDOUT_FILENO) == -1)
			ft_putstr_fd("Error dup2() failed:", 2);
		close(out_fd);
		exe(cmd, env);
	}
	close(out_fd);
	if (waitpid(pid, &exit_cmd, 0) == -1)
		error_message("Error waitpid() failed:", 0);
	if (WEXITSTATUS(exit_cmd) != 0)
		exit(WEXITSTATUS(exit_cmd));
	exit(EXIT_SUCCESS);
}

void	pipe_exe(char *cmd, char **env)
{
	int		pipefds[2];
	pid_t	pid;

	if (pipe(pipefds) == -1)
		error_message("Error pipe() failed:", 0);
	pid = fork();
	if (pid == -1)
		error_message("Error fork() failed:", 0);
	if (pid == 0)
	{
		close(pipefds[0]);
		if (dup2(pipefds[1], 1) == -1)
			ft_putstr_fd("Error dup2() failed:", 2);
		close(pipefds[1]);
		exe(cmd, env);
	}
	close(pipefds[1]);
	dup2(pipefds[0], 0);
	close(pipefds[0]);
}

int	main(int argc, char *argv[], char **envp)
{
	int	index;
	int	f_index;

	if (argc >= 5)
	{
		if (ft_strncmp("here_doc", argv[1], 9) == 0)
		{
			handle_doc(argv[2], &index);
		}
		else
			open_file(argv[1], &index);
		f_index = index;
		while (index < argc - 2)
		{
			pipe_exe(argv[index], envp);
			index++;
		}
		while (wait(NULL) > 0)
			;
		last_cmd(argv[index], envp, argv[argc - 1], f_index);
	}
	else
		error_message("try: ./bpipex  cmd1 cmd2 cmd3 .. file", 0);
	return (0);
}
