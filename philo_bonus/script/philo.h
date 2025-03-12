/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 05:09:01 by emaillet          #+#    #+#             */
/*   Updated: 2025/03/13 00:28:23 by emaillet         ###   ########.fr       */
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
# include <semaphore.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/wait.h>
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
	struct timeval		cur_time;
	long				status;
	int					starve;
	long				id;
	struct timeval		last_eat_time;
	pthread_t			thread;
	long				meal;
	int					isfull;
	int					isdead;
	pid_t				fork_pid;
}	t_philo;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_philo_data
{
	long			fork_c;
	sem_t			*fork_sem;
	long			philo_c;
	long			ttdie;
	long			tteat;
	long			ttsleep;
	long			n_must_eat;
	long			full_count;
	int				was_init;
	struct timeval	start_time;
	int				is_finish;
	sem_t			*philo_edit;
	sem_t			*start;
	sem_t			*wr_msg;
}	t_philo_data;

typedef struct s_philargs
{
	t_philo			*philo;
	t_philo_data	*data;

}	t_philargs;

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
void	wr_philo_msg(t_philo *philo, t_philo_data *data, int status);
long	time_to_ms(struct timeval current_time, struct timeval start_time);
t_philo	*get_philo(long id, t_philo_data *d);

//Philo function
void	data_free(t_philo_data *data, t_list *philo);
void	*philo_loop(t_philargs *arg);
int		philo_lstiter_end(t_list *lst_head, t_philo_data *data);
void	philo_lstiter_pthj(t_list *lst);
int		death_check(t_philo *philo, t_philo_data *data);
void	philo_set_status(t_philo *philo, long status, t_philo_data *data);
void	philosleep(const int ms, t_philo *philo, t_philo_data *data);
#endif
