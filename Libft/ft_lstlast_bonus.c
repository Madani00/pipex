/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:53:02 by eamchart          #+#    #+#             */
/*   Updated: 2025/01/10 19:22:19 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_my_stack	*ft_lstlast(t_my_stack *lst)
{
	t_my_stack	*last;

	last = lst;
	if (!lst)
		return (NULL);
	while (last->next)
	{
		last = last->next;
	}
	return (last);
}
