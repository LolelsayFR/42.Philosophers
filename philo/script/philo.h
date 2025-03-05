/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 05:09:01 by emaillet          #+#    #+#             */
/*   Updated: 2025/03/05 10:47:44 by emaillet         ###   ########.fr       */
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
# include "philo_lang.h"

//Set return value
# define RETURN_ERROR	-1
# define RETURN_SUCCESS	1

//Set the philo macro
# define SLEEP			0
# define EAT			1
# define THINK			2
# define TAKE_FORK		3
# define DEAD			-1

//Set Dev macro
# ifndef PHILO_DEBUG
#  define PHILO_DEBUG	0
# endif
# define ONE_MS			1000

//Set Struct
typedef struct s_philo
{
	long				status;
	int					starve;
	long				id;
	struct s_philo_data	*data;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*shield;
	struct timeval		last_eat_time;
	pthread_t			thread;
	long				meal;
}	t_philo;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_philo_data
{
	struct s_list	*philo;
	long			fork_c;
	long			philo_c;
	long			ttdie;
	long			tteat;
	long			ttsleep;
	long			n_must_eat;
	struct timeval	start_time;
	struct timeval	cur_time;
	long			full_count;
	pthread_mutex_t	*was_init;
	pthread_mutex_t	*mu_philo_c;
	int				is_finish;
}	t_philo_data;

//Utils functions
void	*ft_calloc(size_t nmemb, size_t size);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *lnew);
void	ft_lstadd_back(t_list **lst, t_list *lnew);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
long	ft_atol(const char *str);
t_list	**ft_alist(void);
void	wr_error(char *str);
void	wr_philo_msg(struct timeval time, t_philo *philo);
long	time_to_ms(struct timeval time, t_philo_data *data);
t_philo	*get_philo(long id, t_philo_data *d);

//Philo function
void	data_free(t_philo_data *data);
void	*philo_loop(t_philo *philo);
void	philo_lstiter_pthj(t_list *lst);
void	philo_lstiter_r_fork(t_list *lst_head);
int		death_check(t_philo *philo);
void	philo_set_status(t_philo *philo, long status);
void	philosleep(int ms, t_philo *philo);
#endif
