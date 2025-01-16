/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:56:02 by eamchart          #+#    #+#             */
/*   Updated: 2025/01/10 19:05:51 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_word(char const *str, char c)
{
	const char	*start;
	char		*word;
	int			len;
	int			i;

	start = str;
	len = 0;
	while (*str && *str != c)
	{
		len++;
		str++;
	}
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = start[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

static int	count(const char *s, char c)
{
	int	count;
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i])
		{
			i++;
			count = 0;
		}
		while (s[i] != c && s[i])
		{
			i++;
			count = 1;
		}
		if (count)
		{
			words += count;
		}
	}
	return (words);
}

char	**ft_split(char const *s, char c)
{
	int		len;
	char	**words;
	int		i;

	len = count(s, c);
	words = malloc(sizeof(char *) * (len + 1));
	if (!words)
		return (NULL);
	i = 0;
	while (i < len)
	{
		while (*s == c)
			s++;
		words[i] = get_word(s, c);
		if (!words[i])
			return (NULL);
		i++;
		while (*s && *s != c)
			s++;
	}
	words[i] = NULL;
	return (words);
}
