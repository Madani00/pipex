/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:37:29 by eamchart          #+#    #+#             */
/*   Updated: 2025/02/02 16:13:18 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_spaces(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
		return (2);
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
		ft_putstr_fd("not enough arguments", 2);
		exit(127);
	}
	if (check_spaces(av[2]) == 1)
	{
		ft_puts(av[2], 2);
		ft_putstr_fd(" : command not found", 2);
	}
	if (check_spaces(av[2]) == 2)
		ft_putstr_fd("permission denied:", 2);
	if (check_spaces(av[3]) == 2)
	{
		ft_putstr_fd("permission denied:", 2);
		exit(126);
	}
	if (check_spaces(av[3]))
	{
		ft_puts(av[3], 2);
		ft_putstr_fd(" : command not found", 2);
		exit(127);
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
