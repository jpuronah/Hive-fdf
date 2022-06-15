/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:03:32 by jpuronah          #+#    #+#             */
/*   Updated: 2022/06/13 13:07:33 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

long		ft_atoi(char const *str);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_memcmp(void const *str1, void const *str2, size_t n);
int			ft_strcmp(char const *s1, char const *s2);
int			ft_strncmp(char const *s1, char const *s2, size_t n);
int			ft_strequ(char const *s1, char const *s2);
int			ft_strnequ(char const *s1, char const *s2, size_t n);
int			ft_tolower(int c);
int			ft_toupper(int c);

size_t		ft_strlcat(char *dst, char const *src, size_t dstsize);
size_t		ft_strlen(char const *s);

char		*ft_itoa(int n);
char		*ft_strcat(char *dst, char const *src);
char		*ft_strncat(char *dst, char const *src, size_t n);
char		*ft_strcpy(char *dst, char const *src);
char		*ft_strmap(char const *s, char (*f)(char));
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_strncpy(char *dst, char const *src, size_t len);
char		*ft_strstr(const char *haystack, const char *needle);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strdup(char const *src);
char		*ft_strnew(size_t size);
char		*ft_strtrim(char const *s);
char		*ft_strsub(char const *s, unsigned int start, size_t len);
char		*ft_strstr(const char *haystack, const char *needle);
char		**ft_strsplit(char const *s, char c);

void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memccpy(void *dst, const void *src, int c, size_t n);
void		*ft_memalloc(size_t size);
void		*ft_memchr(const void *s, int c, size_t n);
void		ft_memdel(void **ap);
void		*ft_memmove(void *dst, const void *src, size_t n);
void		*ft_memset(void *dst, int c, size_t n);
void		ft_putchar(char c);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr(const char *str);
void		ft_putstr_fd(char const *s, int fd);
void		ft_putendl(const char *s);
void		ft_putendl_fd(char const *s, int fd);
void		ft_putnbr(int nb);
void		ft_putnbr_fd(int n, int fd);
void		ft_strclr(char *s);
void		ft_strdel(char **as);
void		ft_striter(char *s, void (*f)(char *));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void		ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void		ft_lstadd(t_list **alst, t_list *new);
void		ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list		*ft_lstat(t_list *lst, size_t val);
t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list		*ft_lstnew(void const *content, size_t content_size);

t_list		*ft_create_elem(void *data);

size_t		ft_lstcount(t_list *lst);
void		ft_lstrev(t_list **alst);

int			ft_abs(int i);
size_t		ft_countwords(char *string, char seperator);
int			get_next_line(const int fd, char **line);
int			ft_max(int a, int b);
double		ft_abs_db(double i);
double		ft_max_double(double a, double b);

#endif
