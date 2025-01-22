/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:38:28 by eamchart          #+#    #+#             */
/*   Updated: 2025/01/22 10:06:37 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
