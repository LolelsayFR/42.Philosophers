/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 03:17:48 by emaillet          #+#    #+#             */
/*   Updated: 2025/02/20 04:20:49 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

inline void	data_free(t_philo_data *data)
{
	ft_lstclear(&(data->philo), free);
	ft_lstclear(ft_alist(), free);
}

static inline void	data_init(t_philo_data *data, char **av)
{
	data->fork = ft_atol(av[1]);
	data->ttdie = ft_atol(av[2]);
	data->tteat = ft_atol(av[3]);
	data->ttsleep = ft_atol(av[4]);
	if (av[5] != NULL && av[5][0] != '\0')
		data->t_must_eat = ft_atol(av[5]);
	else
		data->t_must_eat = RETURN_ERROR;
}

int	main(int ac, char **av)
{
	t_philo_data	*data;

	if (ac < 5 || ac > 6)
		return (printf(RED"[ERROR] Invalid args\n"RES));
	ft_lstadd_back(ft_alist(),
		ft_lstnew(data = ft_calloc(1, sizeof(t_philo_data))));
	data_init(data, av);
	if (PHILO_DEBUG)
		printf(YEL"Fork Count = %ld\nTime to die = %ld\nTime to eat = %ld\nTime"
			"to sleep = %ld\nTime each Philo must eat = %ld\n"RES, data->fork,
			data->ttdie, data->tteat, data->ttsleep, data->t_must_eat);
	data_free(data);
	return (RETURN_SUCCESS);
}
