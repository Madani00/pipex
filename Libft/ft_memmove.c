/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:53:38 by eamchart          #+#    #+#             */
/*   Updated: 2024/11/07 11:55:41 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dst;
	const unsigned char	*sorc;

	dst = dest;
	sorc = src;
	if (dest == src)
		return (dest);
	while (n > 0)
	{
		if (dst > sorc)
		{
			*(dst + n - 1) = *(sorc + n - 1);
		}
		else
		{
			*dst++ = *sorc++;
		}
		n--;
	}
	return (dest);
}
