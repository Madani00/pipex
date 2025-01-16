/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:55:26 by eamchart          #+#    #+#             */
/*   Updated: 2024/11/06 18:50:25 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	n_len(long n)
{
	int	len;

	len = 0;
	if (n == 0)
	{
		return (1);
	}
	if (n < 0)
	{
		n = -n;
		len = 1;
	}
	while (n > 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	nb;
	int		len;
	char	*final;

	nb = n;
	len = n_len(nb);
	final = malloc(sizeof(char) * (len + 1));
	if (!final)
		return (NULL);
	final[len] = '\0';
	if (nb == 0)
		final[0] = nb + '0';
	if (nb < 0)
	{
		nb = -nb;
		final[0] = '-';
	}
	while (nb > 0)
	{
		final[--len] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (final);
}
