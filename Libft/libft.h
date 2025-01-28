/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:44:10 by eamchart          #+#    #+#             */
/*   Updated: 2025/01/27 14:05:50 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

char		*ft_strchr(char *s, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
long		ft_atoi(char *nptr);
char		*ft_strdup(char *s);
char		*ft_strjoin(char *s1, char *s2);
char		**ft_split(char const *s, char c);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
int			ft_strcmp(char *s1, char *s2);
size_t		ft_strlen(char *s);
char		*ft_substr(char *s, unsigned int start, size_t len);

#endif
