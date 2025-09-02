/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:30:24 by bcausseq          #+#    #+#             */
/*   Updated: 2025/09/02 19:09:52 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBFT_H
# define LIBFT_H
# define BUFFER_SIZE 69

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdarg.h>
# include <stdint.h>
# include <limits.h>
# include <fcntl.h>

size_t		ft_strlen(const char *s);
char		*ft_strjoin(char *s1, char *s2, bool del_s1, bool del_s2);
void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_strcat(char *dst, const char *src);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		ft_bzero(void *s, size_t n);
char		*ft_strdup(const char *s);
char		*ft_strcpy(char *dst, const char *src);
char		**ft_split(char const *s, char c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char		*get_next_line(int fd);
char		*ft_random_name(char *prefix, int size);
char		*ft_strchr(const char *s, int c);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strrchr(const char *s, int c);
int			count_words(char const *s, char c);
char		*ft_strncpy(char *dest, const char *src, size_t n);
char		*ft_strndup(const char *s, size_t n);
char		*ft_itoa(int n);
int			ft_islower(int c);
int			ft_isupper(int c);
int			ft_isdigit(int c);
int			ft_isdigit_while(char *str);
int			ft_isspace(int c);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
long long	ft_atoll(const char *nptr);
int			ft_putchar_fd(char c, int fd);
int			ft_putstr_fd(const char *s, int fd);
int			ft_putnbr_fd(int n, int fd);

//fprintf
int			ft_fprintf(int fd, char const *src, ...);
int			ft_fpf_conv_cases(int fd, char const *src, va_list list, int *i);
int			ft_fprintf_char(int fd, int *i, char c);
int			ft_fprintf_perc(int fd, int *i);
int			ft_fprintf_digit(int fd, int *i, int disp);
int			ft_fprintf_str(int fd, int *i, char *str);
int			ft_fprintf_hex(int fd, int *i, unsigned int disp, char *mode);
int			ft_putnbr_hex_fd(unsigned long n, int fd, char *mode);
int			ft_putunbr_fd(long long n, int fd);
#endif
