/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 19:52:25 by eamchart          #+#    #+#             */
/*   Updated: 2025/01/26 19:52:58 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	waiting_process(int pid, int spid, int *pipefds)
{
	int	exit_cmd;
	int	exit_spid;

	close(pipefds[0]);
	close(pipefds[1]);
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

int	check_spaces(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
		return (1);
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		else
			return (0);
	}
	return (1);
}

void	args_validate(int argc, char **av)
{
	if (argc != 5)
	{
		ft_putstr_fd("not enough arguments\n", 2);
		exit(127);
	}
	if (check_spaces(av[2]))
	{
		ft_putstr_fd(av[2], 2);
		ft_putstr_fd(" : command not found\n", 2);
	}
	if (check_spaces(av[3]))
	{
		ft_putstr_fd(av[3], 2);
		ft_putstr_fd(" : command not found\n", 2);
		exit(127);
	}
}

void	free_args(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		free(arg[i]);
		i++;
	}
	free(arg);
}

void	free_all(char **args, char *p1)
{
	free_args(args);
	free(p1);
}

void	error_message(char *message, char *file)
{
	if (file)
		ft_putstr_fd(file, 2);
	ft_putstr_fd(message, 2);
	exit(1);
}

