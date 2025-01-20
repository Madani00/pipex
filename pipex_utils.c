/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:00:34 by eamchart          #+#    #+#             */
/*   Updated: 2025/01/20 09:37:11 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void waiting_children(int pid , int spid)
{
	int exit_cmd;
	int exit_spid;

	waitpid(pid, &exit_cmd, 0);
	waitpid(spid, &exit_spid, 0);
	if (WEXITSTATUS(exit_spid) != 0)
	{
		//exit(127);
		exit(WEXITSTATUS(exit_spid));
	}
}
