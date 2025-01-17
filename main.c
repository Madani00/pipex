/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:44:39 by eamchart          #+#    #+#             */
/*   Updated: 2025/01/17 11:57:31 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


char * getenv_path(char **envp)
{
	int i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}



int args_validate_acc(char *cmd1, char *cmd2)
{
	int check;

	check = 0;
	if (access(cmd1, X_OK) != 0)
	{
		check = 1;
	}
	if (access(cmd2, X_OK) != 0)
	{
		check = 2;
	}
	return check;
	// if (access(cmd1, X_OK) != 0)
	// {
	// 	ft_putstr_fd(cmd1, 2);
	// 	ft_putstr_fd(" : command not executable\n", 2);
	// 	check = 1;
	// }
	// if (access(cmd2, X_OK) != 0)
	// {
	// 	ft_putstr_fd(cmd2, 2);
	// 	ft_putstr_fd(" : command not executable\n", 2);
	// 	check = 1;
	// }
	// if (check)
	// 	exit(127);
}

char *get_path(char *cmd, char **env)
{
	char **all_paths;
	char *s_cmd;
	int index;
	char *exe_cmd;

	if (access(cmd, X_OK) == 0)
		return cmd;
	else
	{
		all_paths = ft_split(getenv_path(env), ':');
		s_cmd = ft_strjoin("/", cmd);
		index = 0;
		while (all_paths[index])
		{
			exe_cmd = ft_strjoin(all_paths[index], s_cmd);
			if (access(exe_cmd, X_OK | F_OK) == 0)
			{
				free_all(all_paths, s_cmd, exe_cmd);
				return (exe_cmd);
			}
			free(exe_cmd);
			index++;
		}
	}
	return NULL;
}

void args_validate(int argc, char **av)
{
	int check;

	check = 0;
	if (argc != 5)
	{
		ft_putstr_fd("not enough arguments\n", 2);
		exit(127);
	}
	if (av[2][0] == '\0' || av[2][0] == ' ')
	{
		ft_putstr_fd(av[2], 2);
		ft_putstr_fd(" : command not found\n", 2);
		check = 1;
	}
	if (av[3][0] == '\0' || av[3][0] == ' ')
	{
		ft_putstr_fd(av[3], 2);
		ft_putstr_fd(" : command not found\n", 2);
		check = 1;
	}
	if (check)
		exit(127);
	//args_validate_acc(av[2], av[3]);

}

int main(int argc, char *argv[], char **envp)
{

    args_validate(argc, argv);
	printf("%s ", get_path(argv[2], envp));

    // int infile = open(argv[1], O_RDONLY);
	// if (infile == -1)
	// {
	// 	perror("Error");
	// 	exit(1);
	// }
    // int outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);

    // int pipefds[2];
    // pipe(pipefds);
    // if (fork() == 0) {
    //     // Child process for cmd1
    //     dup2(infile, STDIN_FILENO);
    //     dup2(pipefds[1], STDOUT_FILENO);
    //     close(pipefds[0]);
    //     execve(get_path(argv[2]), parse_args(argv[2]), envp);
    //     exit(1);
    // }

    // if (fork() == 0) {
    //     // Child process for cmd2
    //     dup2(pipefds[0], STDIN_FILENO);
    //     dup2(outfile, STDOUT_FILENO);
    //     close(pipefds[1]);
    //     execve(get_path(argv[3]), parse_args(argv[3]), envp);
    //     exit(1);
    // }

    // close(pipefds[0]);
    // close(pipefds[1]);
    // wait(NULL);
    // wait(NULL);

    // close(infile);
    // close(outfile);

    return 0;
}
