/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 03:17:48 by emaillet          #+#    #+#             */
/*   Updated: 2025/03/04 08:16:55 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "philo_lang.h"
#include <pthread.h>

t_philo	*new_philo(t_philo_data *d)
{
	static long	i = 0;
	t_philo		*new;

	i++;
	new = ft_calloc(1, sizeof(t_philo));
	ft_lstadd_front(ft_alist(),
		ft_lstnew(new->l_fork = ft_calloc(1, sizeof(pthread_mutex_t))));
	if (new == NULL || new->l_fork == NULL)
		return (wr_error(LANG_E_MALLOC), data_free(d), NULL);
	if (new == NULL)
		return (NULL);
	new->data = d;
	new->id = i;
	pthread_mutex_init(new->l_fork, NULL);
	pthread_create(&new->thread, NULL, (void *)philo_loop, (void *)new);
	if (PHILO_DEBUG)
		printf(GRN"Philo thread %ld is created"RES, new->id);
	if (d->fork_c > 200)
	{
		printf(LANG_W LANG_W_TMP LANG_W_CP, new->id, d->philo_c);
		usleep(ONE_MS * 100);
	}
	return (new);
}

void	data_free(t_philo_data *data)
{
	if (PHILO_DEBUG)
		printf("\nFork Count = %ld\nTime to die = %ld\nTime to eat = %ld\nTime"
			" to sleep = %ld\nTime each Philo must eat = %ld\n", data->fork_c,
			data->ttdie, data->tteat, data->ttsleep, data->n_must_eat);
	ft_lstclear(&(data->philo), free);
	ft_lstclear(ft_alist(), free);
}

static void	data_checker(t_philo_data *data)
{
	if (data->philo_c <= 0)
		return (ft_lstclear(ft_alist(), free), wr_error(LANG_E_IPA), exit (-1));
	if (data->ttdie <= 0)
		return (ft_lstclear(ft_alist(), free), wr_error(LANG_E_TTD), exit (-1));
	if (data->tteat <= 0)
		return (ft_lstclear(ft_alist(), free), wr_error(LANG_E_TTE), exit (-1));
	if (data->ttsleep <= 0)
		return (ft_lstclear(ft_alist(), free), wr_error(LANG_E_TTS), exit (-1));
}

static void	data_init(t_philo_data *data, char **av)
{
	static long	i = 0;

	data->philo_c = ft_atol(av[1]);
	data->fork_c = data->philo_c;
	data->ttdie = ft_atol(av[2]);
	data->tteat = ft_atol(av[3]);
	data->ttsleep = ft_atol(av[4]);
	pthread_mutex_init(data->mu_philo_c, NULL);
	pthread_mutex_init(data->mu_philo_c, NULL);
	if (av[5] != NULL && av[5][0] != '\0' && ft_atol(av[5]) > 0)
		data->n_must_eat = ft_atol(av[5]);
	else
		data->n_must_eat = RETURN_ERROR;
	data_checker(data);
	pthread_mutex_lock(data->was_init);
	while (++i <= data->fork_c)
		ft_lstadd_back(&data->philo, ft_lstnew(new_philo(data)));
	philo_lstiter_r_fork(data->philo);
}

int	main(int ac, char **av)
{
	t_philo_data	*data;

	if (ac < 5 || ac > 6)
		return (wr_error(LANG_E_ARG), RETURN_ERROR);
	ft_lstadd_back(ft_alist(),
		ft_lstnew(data = ft_calloc(1, sizeof(t_philo_data))));
	ft_lstadd_front(ft_alist(),
		ft_lstnew(data->mu_philo_c = ft_calloc(1, sizeof(pthread_mutex_t))));
	ft_lstadd_front(ft_alist(),
		ft_lstnew(data->was_init = ft_calloc(1, sizeof(pthread_mutex_t))));
	if (data == NULL || data->mu_philo_c == NULL || data->was_init == NULL)
		return (wr_error(LANG_E_MALLOC), RETURN_ERROR);
	data_init(data, av);
	gettimeofday(&data->start_time, NULL);
	gettimeofday(&data->cur_time, NULL);
	pthread_mutex_unlock(data->was_init);
	while (data->philo_c == data->fork_c && data->full_count <= data->fork_c)
	{
		gettimeofday(&data->cur_time, NULL);
		philo_lstiter_starve_u(data->philo);
	}
	data->is_finish = 1;
	philo_lstiter_pthj(data->philo);
	data_free(data);
	return (RETURN_SUCCESS);
}
