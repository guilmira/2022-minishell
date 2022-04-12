/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:43:09 by guilmira          #+#    #+#             */
/*   Updated: 2022/04/10 11:53:01 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>

/** Buffer_size for get_next_line function. */
# define BUFFER_SIZE 100

/** Struct that stores single direction linked list. */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/** t_bool will only be given values of either 0 or 1 */
typedef int	t_bool;

/*BOOLEANS*/
t_bool	ft_isalnum(int c);
t_bool	ft_isalpha(int c);
t_bool	ft_isascii(int c);
t_bool	ft_isdigit(int c);
t_bool	ft_isprint(int c);
t_bool	ft_isspaces(int c);
/*STRINGS*/
char	*ft_strchr_plus(char *str, char *letters);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(char *s1, char *s2);
size_t	ft_strlen(const char *s);
/*STRINGS MID*/
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *s, int c);
/*STRINGS ADVANCED*/
void	ft_free_split(char **table);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
/*NUMBERS*/
int		ft_atoi_plus(char *str);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
/*FILES*/
void	ft_pointer_fd(unsigned long long n, char *base, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
/*TOOLS*/
int		ft_count_digits_base(int n, int base);
int		ft_count_digits(int n);
char	*ft_tobinary(int n);
int		ft_tolower(int c);
int		ft_toupper(int c);
/*LINKED LISTS*/
void	ft_fullclear(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **alst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
/*MEMORY*/
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *b, int c, size_t len);
/*ARRAYS*/
void	ft_array_print(int *array, int size);
int		*ft_bubble_sort(int *array, int size);
int		*ft_lstto_array(t_list *list, int *array_size);
void	ft_swap(int *a, int *b);
/*ERROR MANAGEMENT*/
int		ft_checkmalloc(void *ptr, char *str);
void		ft_senderror(char *str);
void	ft_shut(char *str);
/*GET NEXT LINE*/
int		get_next_line(int fd, char **line);

#endif
