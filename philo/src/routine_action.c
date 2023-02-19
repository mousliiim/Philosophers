/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_action.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:56:20 by mmourdal          #+#    #+#             */
/*   Updated: 2023/02/19 23:27:53 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_eat(t_philo *philo)
{
	t_info		*info;

	if (!check_die() || philo->eat_count == 0)
		return (0);
	info = starton();
	pthread_mutex_lock(&philo->lock);
	philo->last_eat = gettime() - info->time_start;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_lock(&philo->ceat);
	if (philo->eat_count > 0)
		philo->eat_count--;
	pthread_mutex_unlock(&philo->ceat);
	ft_print(philo, "is eating\n");
	usleep_(info->eat_time);
	return (1);
}

int	ft_sleep_and_think(t_philo *philo)
{
	t_info		*info;

	if (!check_die())
		return (0);
	info = starton();
	ft_print(philo, "is sleeping\n");
	usleep_(info->sleep_time);
	ft_print(philo, "is thinking\n");
	if (info->nb_philo % 2)
	{
		if (info->eat_time >= info->sleep_time)
			usleep((info->eat_time - info->sleep_time) * 1000);
		usleep(500);
	}
	return (1);
}

void	take_fork(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(&philo->fork_left);
		ft_print(philo, "has taken a fork\n");
		pthread_mutex_lock(philo->fork_right);
		ft_print(philo, "has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(philo->fork_right);
		ft_print(philo, "has taken a fork\n");
		pthread_mutex_lock(&philo->fork_left);
		ft_print(philo, "has taken a fork\n");
	}
}

int	ft_print(t_philo *philo, char *str)
{
	t_info		*info;

	info = starton();
	pthread_mutex_lock(&info->print);
	if ((!check_die() && str[0] != 'd')
		|| (philo->eat_count == 0 && str[3] != 'e'))
	{
		pthread_mutex_unlock(&info->print);
		return (0);
	}
	printf("%ld %d %s", (gettime() - info->time_start), philo->id, str);
	pthread_mutex_unlock(&info->print);
	return (1);
}
