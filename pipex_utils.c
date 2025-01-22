/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:00:34 by eamchart          #+#    #+#             */
/*   Updated: 2025/01/22 12:26:54 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	waiting_process(int pid, int spid)
{
	int	exit_cmd;
	int	exit_spid;

	if (waitpid(pid, &exit_cmd, 0) == -1)
		error_message("Error waitpid() failed: \n", 0);
	if (waitpid(spid, &exit_spid, 0) == -1)
		error_message("Error waitpid() failed: \n", 0);
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
