/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:19:44 by eamchart          #+#    #+#             */
/*   Updated: 2025/01/30 15:55:43 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error_message(char *message, char *file)
{
	if (file)
		ft_putstr_fd(file, 2);
	ft_putstr_fd(message, 2);
	exit(1);
}

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

	if (check_spaces(cmd))
	{
		ft_putstr_fd(": command path not found\n", 2);
		exit(127);
	}
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

int	handle_doc(char *limiter, int *index)
{
	int		fds[2];
	int		pid;
	char	*line;

	if (pipe(fds) == -1)
		error_message("Error pipe() failed: \n", 0);
	pid = fork();
	*index = 3;
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
	return (close(fds[1]), fds[0]);
}
