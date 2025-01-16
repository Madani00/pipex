/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:28:10 by eamchart          #+#    #+#             */
/*   Updated: 2024/11/07 09:50:25 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, int n)
{
	unsigned char		*dest;
	const unsigned char	*sorc;

	if (src == dst)
		return (dst);
	dest = dst;
	sorc = src;
	while (n > 0)
	{
		*dest = *sorc;
		dest++;
		sorc++;
		n--;
	}
	return (dst);
}
