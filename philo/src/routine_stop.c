/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_stop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 23:01:32 by mmourdal          #+#    #+#             */
/*   Updated: 2023/02/19 23:31:30 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	check_die(void)
{
	t_info		*info;

	info = starton();
	pthread_mutex_lock(&info->mutex_dead);
	if (!info->die)
	{
		pthread_mutex_unlock(&info->mutex_dead);
		return (0);
	}
	pthread_mutex_unlock(&info->mutex_dead);
	return (1);
}

void	dead_unlock(t_philo *philo, int i)
{
	t_info		*info;

	info = starton();
	pthread_mutex_unlock(&philo[i].lock);
	pthread_mutex_lock(&info->mutex_dead);
	info->die = 0;
	pthread_mutex_unlock(&info->mutex_dead);
	ft_print(&philo[i], "died\n");
}

int	check_philo_eat_count(t_philo *philo)
{
	t_info		*info;
	int			i;
	int			count;

	info = starton();
	i = -1;
	count = 0;
	while (++i < info->nb_philo)
	{
		pthread_mutex_lock(&philo[i].ceat);
		if (philo[i].eat_count == 0)
		{
			pthread_mutex_lock(&info->shield);
			count++;
			pthread_mutex_unlock(&info->shield);
		}
		pthread_mutex_unlock(&philo[i].ceat);
	}
	if (count == info->nb_philo)
		return (1);
	return (0);
}

int	check_dead_philo(t_philo *philo)
{
	t_info		*info;
	int			i;

	info = starton();
	while (info->die)
	{
		i = -1;
		while (++i < info->nb_philo)
		{
			pthread_mutex_lock(&philo[i].lock);
			if (gettime() - info->time_start
				- philo[i].last_eat >= info->limit_die)
				return (dead_unlock(philo, i), 0);
			pthread_mutex_unlock(&philo[i].lock);
			if (check_philo_eat_count(philo) == 1)
			{
				pthread_mutex_lock(&info->mutex_dead);
				info->die = 0;
				pthread_mutex_unlock(&info->mutex_dead);
			}
		}
		usleep(500);
	}
	return (0);
}
