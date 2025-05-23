/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 04:07:02 by emaillet          #+#    #+#             */
/*   Updated: 2025/05/07 16:48:54 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_strlen_skip_zero(const char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] == '0' || str[i] == '+' || str[i] == '-' || str[i] != '\0')
		i++;
	while (str[i] != '\0')
	{
		i++;
		count++;
	}
	return (count);
}

static int	ft_isdigit(int c)
{
	if (!c)
		return (0);
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long	ft_atol(const char *str)
{
	long	val;
	long	sign;
	long	i;

	if (!str || ft_strlen_skip_zero(str) > 12)
		return (0);
	val = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		val = val * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (RETURN_ERROR);
	return (val * sign);
}
