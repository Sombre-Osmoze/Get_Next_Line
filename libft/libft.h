/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcusflorentin <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 20:32:47 by marcusflo         #+#    #+#             */
/*   Updated: 2017/11/22 23:18:51 by mflorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

typedef struct	s_item
{
	void			*content;
	void			*content_ref;
	size_t			content_size;
	size_t			row;
	struct s_item	*prev;
	struct s_item	*next;
	struct s_ctrl	*ctrl;
}				t_item;

typedef struct	s_ctrl
{
	size_t			nb_item;
	struct s_item	*head;
	struct s_item	*tail;
	struct s_item	*curr;
	struct s_item	*last_ac;
}				t_ctrl;

t_ctrl			*ft_init_ctrl(void);
t_item			*ft_get_item(t_ctrl *ctrl, size_t pos);
t_item			*ft_search_item(t_ctrl *ctrl, const void *ref, int i,
						int (*cmp)(const void *cmp, const void *ref));
t_item			*ft_create_item(t_ctrl *ctrl, size_t pos);
t_item			*ft_rm_item(t_ctrl *ctrl, size_t pos);
void			ft_clean_list(t_ctrl *ctrl);
void			ft_rm_list(t_ctrl *ctrl);
void			ft_rm_ctrl(t_ctrl *ctrl);
void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
const void		*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t len);
char			*ft_strcat(char *s1, char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
const char		*ft_strchr(const char *s, int c);
const char		*ft_strrchr(const char *s, int c);
const char		*ft_strstr(const char *haystack, const char *needle);
const char		*ft_strnstr(const char *hayst, const char *needle, size_t len);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *str);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(const char *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(const char *s1, const char *s2);
int				ft_strnequ(const char *s1, const char *s2, size_t n);
char			*ft_strsub(const char *s, unsigned int start, size_t len);
char			*ft_strjoin(const char *s1, const char *s2);
char			*ft_strtrim(const char *s);
void			ft_strswp(char *s1, char *s2);
void			ft_strnswp(char *s1, char *s2, int n);
void			ft_strlswp(char *s1, char *s2);
void			ft_memswp(void *a, void *b, size_t len);
size_t			ft_memicmp(const char *s1, const char *s2, size_t len);
char			*ft_itoa(int n);
char			**ft_strsplit(char const *s, char c);
void			ft_putchar(char c);
void			ft_putstr(const char *s);
void			ft_putendl(const char *s);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(const char *s, int fd);
void			ft_putendl_fd(const char *s, int fd);
void			ft_putnbr_fd(int nb, int fd);
t_list			*ft_lstnew(void const *content, size_t csize);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_putnbr(int nb);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int				ft_stricpy(char *dst, const char *src);
void			*ft_memjoin(void *head, size_t head_size,
							void *tail, size_t tail_size);
int				ft_int_cmp(const void *cmp, const void *ref);
size_t			ft_abs(long long nb);
size_t			ft_memichr(const void *src, char chr, size_t len);
char			*ft_strnjoin(const char *s1, size_t n1,
													const char *s2, size_t n2);

#endif
