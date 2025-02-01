/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:00:34 by eamchart          #+#    #+#             */
/*   Updated: 2025/02/01 21:52:03 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	waiting_process(int pid, int spid, int *pipefds)
{
	int	exit_cmd;
	int	exit_spid;

	close(pipefds[0]);
	close(pipefds[1]);
	if (waitpid(pid, &exit_cmd, 0) == -1)
		error_message("Error waitpid() failed:", 0);
	if (waitpid(spid, &exit_spid, 0) == -1)
		error_message("Error waitpid() failed:", 0);
	if (WEXITSTATUS(exit_spid) != 0)
	{
		exit(WEXITSTATUS(exit_spid));
	}
}

char	*getenv_path(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
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
