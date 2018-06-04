/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 15:42:33 by ltanenba          #+#    #+#             */
/*   Updated: 2018/04/24 15:08:29 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>

/*
** Libc Funks
*/

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *b, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(char const *str);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *h, const char *n, size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isascii(int c);
int					ft_isalnum(int c);
int					ft_isprint(int c);

/*
** Additional Funks
*/

void				ft_putchar_fd(char c, int fd);
void				ft_putchar(char c);
void				ft_putstr_fd(char const *str, int fd);
void				ft_putstr(char const *str);
void				ft_putnbr_fd(int n, int fd);
void				ft_putnbr(int n);
void				ft_putendl(char const *str);
void				ft_putendl_fd(char const *str, int fd);
char				*ft_itoa(int n);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **ap);
void				ft_strclr(char *str);
void				ft_striter(char *s, void (*funk)(char *));
void				ft_striteri(char *s, void (*funk)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*funk)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
int					ft_strjoin_free(char **dst, char *src);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);

/*
** Bonus Funks
*/

# ifndef S_LIST
#  define S_LIST

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

# endif

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **lst, t_list *n);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

/*
** Extra Funks
*/

char				*ft_itoa_base(int n, int base);
char				*ft_strrev(char *str);
int					ft_isspace(char c);
char				*ft_strjoin_null(char const *s1, char const *s2);
int					ft_isupper(int c);
int					ft_islower(int c);
void				ft_lstsort(t_list **head, int (*cmp)(void *, void *));
int					ft_numlen_base(long n, int base);
int					ft_copyuntil(char **dst, char *src, char c);

/*
** Get Next Line
*/

# define BUFF_SIZE 42

# define GNL_MALLOC_CHECK(x) if (!(x)) return (-1);

int					get_next_line(const int fd, char **line);

/*
** Circular Lists
*/

typedef struct		s_clist
{
	struct s_clist	*left;
	struct s_clist	*right;
	struct s_clist	*up;
	struct s_clist	*down;
	struct s_clist	*head;
	char			*id;
	size_t			content_size;
	void			*content;
}					t_clist;

t_clist				*ft_lstcnew(void *content, size_t content_size, char *id);
void				ft_delinkud(t_clist *n);
void				ft_delinklr(t_clist *n);
void				ft_relinkud(t_clist *n);
void				ft_relinklr(t_clist *n);
void				ft_lstcaddl(t_clist *lst, t_clist *n);
void				ft_lstcaddr(t_clist *lst, t_clist *n);
void				ft_lstcaddu(t_clist *lst, t_clist *n);
void				ft_lstcaddd(t_clist *lst, t_clist *n);

#endif
