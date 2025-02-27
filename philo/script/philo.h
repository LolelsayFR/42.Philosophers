/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 05:09:01 by emaillet          #+#    #+#             */
/*   Updated: 2025/02/27 08:11:31 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <limits.h>
# include <string.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

//Set return value
# define RETURN_ERROR	-1
# define RETURN_SUCCESS	1

//Set the philo macro
# define SLEEP			0
# define EAT			1
# define THINK			2
# define DEAD			-1

//Set Dev macro
# ifndef PHILO_DEBUG
#  define PHILO_DEBUG	1
# endif

//Set color strings
# define RED			"\x1B[31m"
# define GRN			"\x1B[32m"
# define YEL			"\x1B[33m"
# define RES			"\x1B[0m"

//Set Struct
typedef struct s_philo
{
	long				status;
	long				id;
	struct s_philo_data	*data;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
	struct timeval		last_eat_time;
	pthread_t			thread;
}	t_philo;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_philo_data
{
	struct s_list	*philo;
	struct s_list	*fork;
	long			fork_c;
	long			ttdie;
	long			tteat;
	long			ttsleep;
	long			t_must_eat;
	struct timeval	start_time;
	struct timeval	cur_time;
	struct timeval	last_time;
	long			loop_count;
}	t_philo_data;

//Utils functions
void	*ft_calloc(size_t nmemb, size_t size);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *lnew);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *lnew);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
long	ft_atol(const char *str);
t_list	*ft_lst_rotate(t_list **lst, size_t n);
t_list	*ft_lst_unrotate(t_list **lst, size_t n);
void	ft_lst_swap(t_list **a, t_list **b);
t_list	**ft_alist(void);

//Philo function
void	data_free(t_philo_data *data);
void	*philo_loop(void *philo);
void	philo_lstiter_pthj(t_list *lst);

#endif
