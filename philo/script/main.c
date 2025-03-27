/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:08:25 by emaillet          #+#    #+#             */
/*   Updated: 2025/03/27 19:05:44 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "philo_lang.h"

t_philo	*new_philo(t_philo_data *d, t_list *philo)
{
	static long	i = 0;
	t_philo		*new;

	i++;
	new = ft_calloc(1, sizeof(t_philo));
	if (new == NULL)
		return (wr_error(LANG_E_MALLOC), data_free(d, philo), NULL);
	ft_alist_add_front(new->l_fork = ft_calloc(1, sizeof(pthread_mutex_t)));
	if (new->l_fork == NULL)
		return (wr_error(LANG_E_MALLOC), data_free(d, philo), NULL);
	new->id = i;
	pthread_mutex_init(new->l_fork, NULL);
	pthread_mutex_init(&new->state_mutex, NULL);
	if (PHILO_DEBUG)
		printf(GRN"Philo thread %ld is created"RES, new->id);
	return (new);
}

void	data_free(t_philo_data *data, t_list *philo)
{
	pthread_mutex_lock(data->philo_edit);
	pthread_mutex_lock(data->wr_msg);
	data->is_finish = 1;
	pthread_mutex_unlock(data->philo_edit);
	pthread_mutex_unlock(data->wr_msg);
	usleep(ONE_MS * 10);
	philo_lstiter_pthj(philo);
	ft_lstclear(&philo, free);
	ft_alist_free();
}

static int	data_checker(t_philo_data *data, char **av)
{
	if (av[5] != NULL && av[5][0] != '\0' && ft_atol(av[5]) > 0
		&& ft_atol(av[5]) < LONG_MAX)
		data->n_must_eat = ft_atol(av[5]);
	else
		data->n_must_eat = -1;
	if (data->philo_c <= 0 || data->philo_c > 200)
		return (ft_lstclear(ft_alist(), free), wr_error(LANG_E_IPA), -1);
	if (data->ttdie <= 0 || data->ttdie > INT_MAX)
		return (ft_lstclear(ft_alist(), free), wr_error(LANG_E_TTD), -1);
	if (data->tteat <= 0 || data->tteat > INT_MAX)
		return (ft_lstclear(ft_alist(), free), wr_error(LANG_E_TTE), -1);
	if (data->ttsleep <= 0 || data->ttsleep > INT_MAX)
		return (ft_lstclear(ft_alist(), free), wr_error(LANG_E_TTS), -1);
	return (1);
}

static int	data_init(t_philo_data *data, char **av, t_list **philo)
{
	static long	i = 0;

	pthread_mutex_init(data->shield, NULL);
	pthread_mutex_init(data->philo_edit, NULL);
	pthread_mutex_init(data->wr_msg, NULL);
	data->philo_c = ft_atol(av[1]);
	data->fork_c = data->philo_c;
	data->ttdie = ft_atol(av[2]);
	data->tteat = ft_atol(av[3]);
	data->ttsleep = ft_atol(av[4]);
	if (data_checker(data, av) == -1)
		return (-1);
	while (++i <= data->fork_c)
		ft_lstadd_front(philo, ft_lstnew(new_philo(data, *philo)));
	if (data->fork_c > 1)
		philo_lstiter_r_fork(*philo, data);
	return (data->was_init = 1);
}

int	main(int ac, char **av)
{
	t_philo_data	*data;
	t_list			*philo;

	if (ac < 5 || ac > 6)
		return (wr_error(LANG_E_ARG), RETURN_ERROR);
	ft_alist_add_front(data = ft_calloc(1, sizeof(t_philo_data)));
	ft_alist_add_back(data->philo_edit = ft_calloc(1, sizeof(pthread_mutex_t)));
	ft_alist_add_front(data->shield = ft_calloc(1, sizeof(pthread_mutex_t)));
	ft_alist_add_front(data->wr_msg = ft_calloc(1, sizeof(pthread_mutex_t)));
	philo = NULL;
	if (data == NULL || data->philo_edit == NULL || data->shield == NULL
		|| data->wr_msg == NULL)
		return (wr_error(LANG_E_MALLOC), RETURN_ERROR);
	if (data_init(data, av, &philo) == -1)
		return (RETURN_ERROR);
	philo_launcher(philo, data);
	while (philo_lstiter_end(philo, data))
		philo_lstiter_end(philo, data);
	if (PHILO_DEBUG)
		printf(YEL"MAIN LOOP FINISHED"RES);
	data_free(data, philo);
	return (RETURN_SUCCESS);
}
