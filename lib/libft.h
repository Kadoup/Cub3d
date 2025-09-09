/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:12:08 by kadoup            #+#    #+#             */
/*   Updated: 2025/09/09 18:43:12 by tjourdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <limits.h>
# include <fcntl.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

size_t	ft_strlen(const char *str);
int		ft_printf(const char *format, ...);
int		putptr(void *p);
int		putcharint(char c);
int		putstrint(char *s);
int		putunbrint(unsigned int nb);
int		putnbrint(int nb);
int		putnbr_base_recurse(unsigned long nb, char *base, unsigned int baselen);
int		putnbr_baseint(unsigned long nb, char *base);
void	ft_bzero(void *s, size_t n);
char	*ft_strdup(const char *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
void	*ft_memset(void *s, int c, size_t n);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
void	ft_putchar_fd(char c, int fd);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strchr(const char *s, int c);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int nb, int fd);
void	ft_putendl_fd(char *s, int fd);
void	*ft_memchr(const void *s, int c, size_t n);
char	*ft_itoa(int n);
long	ft_atoi(const char *str);
void	*ft_calloc(size_t nmemb, size_t size);
char	*gnl(int fd);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	**ft_split(char const *s, char c);
typedef struct s_list
{
	int				value;
	int				index;
	struct s_list	*next;
}					t_list;
t_list	*ft_lstnewi(int content, int index);
t_list	*ft_lstnew(int content);
t_list	*ft_lstprevlast(t_list *lst);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst);
void	ft_lstclear(t_list **lst);
void	ft_lstiter(t_list *lst, void (*f)(int));
t_list	*ft_lstmap(t_list *lst, int (*f)(int));
void	ft_putstr(char *s);
void	ft_putchar(char c);
void	ft_putnbr(int nb);
void	ft_putnbr_base(unsigned long nb, char *base);
void	ft_putunbr(unsigned int nb);
void	ft_lstswap(t_list	**res);
void	ft_lstpush(t_list **fromlist, t_list **tolist);
void	ft_lstrotate(t_list **list);
void	ft_lstrrotate(t_list **list);
int		ft_abs(int n);

#endif