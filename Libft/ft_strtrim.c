/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:28:12 by eamchart          #+#    #+#             */
/*   Updated: 2025/01/09 16:47:18 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	first_index(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i] != '\0')
	{
		j = 0;
		while (set[j] != '\0' && s1[i] != set[j])
			j++;
		if (s1[i] != set[j])
			break ;
		i++;
	}
	return (i);
}

static int	last_index(char const *s1, char const *set, int start, int len)
{
	int	j;

	while (len > start)
	{
		j = 0;
		while (set[j] != '\0' && s1[len] != set[j])
			j++;
		if (s1[len] != set[j])
			break ;
		len--;
	}
	return (len);
}

char	*ft_strtrim(char *s1, char *set)
{
	char	*new;
	int		start;
	int		end;
	int		total;
	int		len;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	len = ft_strlen(s1);
	start = first_index(s1, set);
	end = last_index(s1, set, start, len);
	if (start == len)
		return (ft_strdup(""));
	total = end - start + 1;
	new = malloc(sizeof(char) * (total + 1));
	if (!new)
		return (NULL);
	ft_memcpy(new, s1 + start, total);
	new[total] = '\0';
	return (new);
}
