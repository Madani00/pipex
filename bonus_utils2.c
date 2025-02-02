/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:19:44 by eamchart          #+#    #+#             */
/*   Updated: 2025/02/02 16:20:27 by eamchart         ###   ########.fr       */
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
		ft_putstr_fd(": command not found", 2);
		exit(127);
	}
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

void	check_dots(char **dots)
{
	if ((*dots[0] == '.' && (ft_strlen(*dots) == 1)))
	{
		ft_putstr_fd(" : command not found", 2);
		free_args(dots);
		exit(127);
	}
	if ((*dots[0] == '.' && (ft_strlen(*dots) == 2)))
	{
		ft_putstr_fd(" : command not found", 2);
		free_args(dots);
		exit(127);
	}
}
