/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:44:39 by eamchart          #+#    #+#             */
/*   Updated: 2025/01/20 13:13:55 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char * getenv_path(char **envp)
{
	int i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char *get_path2(char *cmd, char **env)
{
	char **all_paths;
	char *s_cmd;
	int index;
	char *exe_cmd;
	char *path_env;

	path_env = getenv_path(env);
	if (!path_env)
		return NULL;
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

char *get_path(char *cmd, char **env)
{
	char *path;

	if (access(cmd, F_OK | X_OK) == 0)
		return cmd;
	path = get_path2(cmd, env);
	if (!path)
		return (NULL);
	return (path);
}

void exe(char *cmd, char **env)
{
	char **cmd1_op;
	char *path;

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
		//free(path);
		free_args(cmd1_op);
		exit(127);
	}
}


void first_cmd(char **env, char *cmd1, int file1, int *pipefds)
{
	dup2(file1, STDIN_FILENO);
    dup2(pipefds[1], STDOUT_FILENO);
	write(2, &pipefds[0], 1);

    close(pipefds[0]);
	//close(pipefds[1]); // i added this
	exe(cmd1, env);
}

void second_cmd(char **env, char *cmd2, int file2, int *pipefds)
{
	dup2(pipefds[0], STDIN_FILENO);
    dup2(file2, STDOUT_FILENO);

	//close(pipefds[0]); // i added this
    close(pipefds[1]);
	exe(cmd2, env);
}

void error_message(char *message, char *file)
{
	if (file)
		ft_putstr_fd(file, 2);
	ft_putstr_fd(message, 2);
	exit(1);
}

int main(int argc, char *argv[], char **envp)
{
	int  file1;
	int  file2;
	int pipefds[2];
	pid_t pid_1;
	pid_t pid_2;

	args_validate(argc, argv);
	file1 = open(argv[1], O_RDONLY);
	if (file1 == -1)
		error_message(" : No such file\n", argv[1]);
	file2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file2 == -1)
		error_message(" : No such file\n", argv[4]);
    if (pipe(pipefds) == -1)
		error_message("Error pipe() failed: \n", 0);

	pid_1 = fork();
    if (pid_1 == 0)
	{
		first_cmd(envp, argv[2], file1, pipefds);
        // dup2(file1, STDIN_FILENO);
        // dup2(pipefds[1], STDOUT_FILENO);
        // close(pipefds[0]);
		// //close(pipefds[1]); // i added this
		// exe(argv[2], envp);
    }
	pid_2 = fork();
    if (pid_2 == 0)
	{
		second_cmd(envp, argv[3], file2, pipefds);
        // dup2(pipefds[0], STDIN_FILENO);
        // dup2(file2, STDOUT_FILENO);
		// //close(pipefds[0]); // i added this
        // close(pipefds[1]);
		// exe(argv[3], envp);
    }
	if (pid_1 == -1 || pid_2 == -1)
		error_message("Error fork() failed: \n", 0);
	close(pipefds[0]);
	close(pipefds[1]);
	waiting_children(pid_1, pid_2);
	return (0);
}
