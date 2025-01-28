/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 21:29:13 by eamchart          #+#    #+#             */
/*   Updated: 2025/01/28 22:02:03 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*get_path2(char *cmd, char **env)
{
	char	**all_paths;
	char	*s_cmd;
	int		index;
	char	*exe_cmd;
	char	*path_env;

	path_env = getenv_path(env);
	if (!path_env || ft_strchr(cmd, '/'))
		return (NULL);
	all_paths = ft_split(path_env, ':');
	s_cmd = ft_strjoin("/", cmd);
	index = 0;
	while (all_paths && all_paths[index])
	{
		exe_cmd = ft_strjoin(all_paths[index], s_cmd);
		if (access(exe_cmd, X_OK | F_OK) == 0)
		{
			free_all(all_paths, s_cmd);
			return (exe_cmd);
		}
		free(exe_cmd);
		index++;
	}
	free_all(all_paths, s_cmd);
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	char	*path;

	if (access(cmd, X_OK) == 0 && ft_strchr(cmd, '/'))
		return (cmd);
	else if (access(cmd, X_OK) == 0 && !getenv_path(env))
		return (NULL);
	path = get_path2(cmd, env);
	if (!path)
		return (NULL);
	return (path);
}

void	exe(char *cmd, char **env)
{
	char	**cmd1_op;
	char	*path;

	cmd1_op = ft_split(cmd, ' ');
	path = get_path(cmd1_op[0], env);
	if (!path)
	{
		ft_putstr_fd(cmd1_op[0], 2);
		ft_putstr_fd(": command path not found\n", 2);
		free_args(cmd1_op);
		exit(127);
	}
	if (execve(path, cmd1_op, env) == -1)
	{
		ft_putstr_fd(cmd1_op[0], 2);
		ft_putstr_fd(" : command not executable\n", 2);
		free_args(cmd1_op);
		exit(127);
	}
}


int handle_doc(char *limiter)
{
	int fds[2];
	int pid;
	char *line;

	pipe(fds);
	pid = fork();
	if (pid == 0)
	{
		close(fds[0]);
		line = get_next_line(0);
		while (line)
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			{
				free(line);
				close(fds[1]);
				exit(0);
			}
			write(fds[1], line, ft_strlen(line));
			free(line);
			line = get_next_line(0);
		}
	}
	close(fds[1]);
	return fds[0];
}

int apply_command(char *cmd, char **env, int read_fd, int out_fd)
{
	int pid;

	pid = fork();

	if (pid == 0)
	{
		dup2(read_fd, 0);
		dup2(out_fd, 1);
		if (check_spaces(cmd))
			exit(127);
		exe(cmd, env);
	}
	close(read_fd);
	close(out_fd);
	//wait(NULL); // mm w it program works
	return pid;
}


void	waiting_process(int pid)
{
	int	exit_cmd;
waitpid(pid, &exit_cmd, 0);
	// if (waitpid(pid, &exit_cmd, 0) == -1)
	// 	error_message("Error waitpid() failed: \n", 0);
	if (WEXITSTATUS(exit_cmd) != 0)
	{
		exit(WEXITSTATUS(exit_cmd));
	}
	exit(0);
}

int	main(int argc, char *argv[], char **envp)
{

	int index;
	int		pipefds[2];
	int last_file;
	int read_fd;
	int pid;

	last_file = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (argc >= 5)
	{
		if (ft_strncmp("here_doc", argv[1], 9) == 0)
		{
			index = 3;
			read_fd = handle_doc(argv[2]);
		}
		else
		{
			index = 2;
			read_fd = open(argv[1], O_RDONLY);
			if (read_fd == -1)
				error_message(" : No such file or directory", argv[1]);
		}
		while (index < argc - 2)
		{
			pipe(pipefds);
			apply_command(argv[index], envp, read_fd, pipefds[1]);
			//close(pipefds[1]);
			read_fd = pipefds[0];
			index++;
		}
		pid = apply_command(argv[index], envp, read_fd, last_file);
		close(last_file);
		waiting_process(pid);
	}
	else
		error_message("try: ./bpipex  cmd1 cmd2 cmd3 .. file\n", 0);
}
