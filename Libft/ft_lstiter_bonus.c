/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:05:23 by eamchart          #+#    #+#             */
/*   Updated: 2025/01/10 19:22:11 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_my_stack *lst, int (*f)(int))
{
	if (!f || !lst)
		return ;
	while (lst)
	{
		f(lst->data);
		lst = lst->next;
	}
}
