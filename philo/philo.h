/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 05:09:01 by emaillet          #+#    #+#             */
/*   Updated: 2025/05/09 14:51:53 by emaillet         ###   ########.fr       */
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
# include <stdbool.h>
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

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				id_next_fork;
	int				status;
	bool			is_alive;
	bool			is_full;
	struct timeval	last_update;
	struct timeval	last_eat;
	struct s_phdata	*data;
}	t_philo;

typedef struct s_phdata
{
	bool			was_init;
	bool			is_running;
	int				n_fork;
	int				n_philo;
	int				ttdie;
	int				tteat;
	int				ttsleep;
	int				n_must_eat;
	struct timeval	start_time;
	pthread_mutex_t	**phforks;
	t_philo			**philo;
	pthread_t		monitor;
}	t_phdata;

/* FUNCTIONS */
void		philo_set_status(t_philo *philo, long status, t_phdata *data);
void		wr_philo_msg(t_philo *philo, t_phdata *data, int status);
void		ms_sleep(const int ms, t_philo *philo);
bool		death_check(t_philo *philo);
long		time_to_ms(struct timeval current_time, struct timeval start_time);
void		*philo_loop(t_philo *philo);
t_phdata	*get_data(void);
void		ft_lstadd_back(t_list **lst, t_list *lnew);
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstdelone(t_list *lst, void (*del)(void*));
t_list		*ft_lstnew(void *content);
int			ft_freetab(void **tab);
void		ft_alist_add_back(void *content);
void		ft_alist_free(void);
t_list		**ft_alist(void);
long		ft_atol(const char *str);
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_putendl_fd(char *s, int fd);

#endif
