/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:20:49 by maabdull          #+#    #+#             */
/*   Updated: 2024/08/18 19:36:40 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

void	ft_putendl_fd(const char *s, int fd);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(const char *str1, const char *str2);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *str);
char	*get_next_line(int fd);

#endif
