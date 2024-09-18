/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:20:49 by maabdull          #+#    #+#             */
/*   Updated: 2024/09/18 22:55:46 by maabdull         ###   ########.fr       */
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

# ifndef WHITESPACE
#  define WHITESPACE " \t\n\v\r"
# endif

int		ft_atoi(const char *str);
int		ft_err(char *msg);
void	ft_freetab(char **arr);
void	ft_puttab(char **arr);
void	ft_putendl_fd(const char *s, int fd);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strac(char *str, char c);
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *str);
char	*ft_strjoin(const char *str1, const char *str2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_tabdup(char **tab, char fill_char);
char	**ft_tabjoin(char **tab, char *str);
int		ft_tablen(char **tab);

#endif
