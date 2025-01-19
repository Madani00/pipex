/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:37:29 by eamchart          #+#    #+#             */
/*   Updated: 2025/01/19 15:38:23 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int check_spaces(char *str)
{
	int i = 0;

	if (str[0] == '\0')
        return 1;
	while (str[i])
	{
        if (str[i] == ' ')
            i++;
        else
			return (0);
    }
    return 1;
}

void args_validate(int argc, char **av)
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
