/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 19:27:41 by eamchart          #+#    #+#             */
/*   Updated: 2025/02/02 16:04:43 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	check_dots(cmd1_op);
	path = get_path(cmd1_op[0], env);
	if (!path)
	{
		ft_puts(cmd1_op[0], 2);
		ft_putstr_fd(": command path not found", 2);
		free_args(cmd1_op);
		exit(127);
	}
	if (execve(path, cmd1_op, env) == -1)
	{
		ft_puts(cmd1_op[0], 2);
		ft_putstr_fd(" : Permission denied", 2);
		free_args(cmd1_op);
		exit(126);
	}
}

void	first_cmd(char **env, char *cmd1, int file1, int *pipefds)
{
	close(pipefds[0]);
	if (dup2(file1, STDIN_FILENO) == -1)
		ft_putstr_fd("Error dup2() cmd1 failed:", 2);
	if (dup2(pipefds[1], STDOUT_FILENO) == -1)
		ft_putstr_fd("Error dup2() cmd1 failed:", 2);
	close(file1);
	close(pipefds[1]);
	if (check_spaces(cmd1))
		exit(127);
	exe(cmd1, env);
}

void	second_cmd(char **env, char *cmd2, int file2, int *pipefds)
{
	close(pipefds[1]);
	if (dup2(pipefds[0], STDIN_FILENO) == -1)
		ft_putstr_fd("Error dup2() cmd2 failed:", 2);
	if (dup2(file2, STDOUT_FILENO) == -1)
		ft_putstr_fd("Error dup2() cmd2 failed:", 2);
	close(file2);
	close(pipefds[0]);
	exe(cmd2, env);
}

int	main(int argc, char *argv[], char **envp)
{
	int		file1;
	int		file2;
	int		pipefds[2];
	pid_t	pid_1;
	pid_t	pid_2;

	args_validate(argc, argv);
	file1 = open(argv[1], O_RDONLY);
	if (file1 == -1)
		error_message(" : No such file or directory", argv[1]);
	file2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file2 == -1)
		error_message(" : No such file or directory", argv[4]);
	if (pipe(pipefds) == -1)
		error_message("Error pipe() failed:", 0);
	pid_1 = fork();
	if (pid_1 == 0)
		first_cmd(envp, argv[2], file1, pipefds);
	pid_2 = fork();
	if (pid_2 == 0)
		second_cmd(envp, argv[3], file2, pipefds);
	if (pid_1 == -1 || pid_2 == -1)
		error_message("Error fork() failed:", 0);
	waiting_process(pid_1, pid_2, pipefds);
	return (0);
}
