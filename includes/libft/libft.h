/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpereir <arpereir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:20:50 by arpereir          #+#    #+#             */
/*   Updated: 2025/05/03 18:55:49 by arpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <limits.h>

/* ************************************************************************** */
/*                              Character Checks                              */
/* ************************************************************************** */

int				ft_isalnum(int arg);
int				ft_isalpha(int c);
int				ft_isascii(int arg);
int				ft_isdigit(int c);
int				ft_isprint(int arg);
int				ft_tolower(int arg);
int				ft_toupper(int arg);

/* ************************************************************************** */
/*                                Memory Functions                            */
/* ************************************************************************** */

void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t n_memb, size_t size);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memset(void *s, int c, size_t n);

/* ************************************************************************** */
/*                                String Functions                            */
/* ************************************************************************** */

size_t			ft_strlen(char const *str);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
unsigned int	ft_strlcat(char *dst, const char *src, unsigned int size);
unsigned int	ft_strlcpy(char *dest, char const *src, unsigned int size);
char			*ft_strdup(char *src);
int				ft_strncmp(char const *s1, char const *s2, size_t n);
char			*ft_strnstr(const char *haystack, const char *needle,
					size_t len);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			**ft_split(char const *s, char c);
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/* ************************************************************************** */
/*                                Conversion Functions                        */
/* ************************************************************************** */

int				ft_atoi(const char *str);
char			*ft_itoa(int n);

/* ************************************************************************** */
/*                                 Output Functions                           */
/* ************************************************************************** */

void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int nb, int fd);

#endif
