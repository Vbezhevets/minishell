/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalerii <bvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:37:06 by bvalerii          #+#    #+#             */
/*   Updated: 2024/07/18 18:59:33 by bvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# define BUFFER_SIZE 10

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_strlen(char *str);
void	*ft_memset(void *str, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *to, void *from, size_t n);
void	*ft_memmove(void *to, void *from, size_t n);
int		ft_strlcpy(char *dst, char *src, size_t n);
void	ft_strcpy(char *dst, char *src);
size_t	ft_strlcat(char *dst, char *src, size_t n);
int		ft_toupper(int ch);
int		ft_tolower(int ch);
char	*ft_strchr(char *str, int c);
char	*ft_strrchr(char *str, int c);
int		ft_strncmp(char *str1, const char *str2, size_t n);
void	*ft_memchr(void *str, int c, size_t n);
int		ft_memcmp(void *s1, void *s2, size_t n);
char	*ft_strnstr(char *big, char *little, size_t len);
int		ft_atoi(char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(char *src);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_str3join(char *a, char *b, char *c);
char	*ft_strtrim(char *s1, char *set);
char	**ft_split(char *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*get_next_line(int fd);
int		ft_printf(char *str, ...);
void	ft_putnbr(long long int n, int *count);
void	ft_putchr(char c, int *count);
void	ft_putstr(char *s, int *count);
void	ft_putunbr(unsigned int n, int *count);
void	ft_putpntr(void *pntr, int *count);
void	ft_putx(int n, int *count);
void	ft_put_x(int n, int *count);
#endif
