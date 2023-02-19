/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:30:57 by mmourdal          #+#    #+#             */
/*   Updated: 2023/02/19 03:42:53 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/*
memset
printf
malloc
free
write
usleep
gettimeofday 
pthread_create
pthread_detach 
pthread_join
pthread_mutex_init
pthread_mutex_destroy
pthread_mutex_lock
pthread_mutex_unlock
*/

t_info	*starton(void)
{
	static t_info	info;

	return (&info);
}

void	ft_init_info(t_info *info, int argc, char **argv)
{
	info->limit_die = ft_atoi(argv[2]);
	info->eat_time = ft_atoi(argv[3]);
	info->sleep_time = ft_atoi(argv[4]);
	info->die = 1;
	if (argc == 6)
		info->need_eat = ft_atoi(argv[5]);
	else
		info->need_eat = 0;
}

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

int	ft_print(t_philo *philo, char *str)
{
	t_info		*info;

	info = starton();
	pthread_mutex_lock(&info->print);
	if (!check_die() && str[0] != 'd')
	{
		pthread_mutex_unlock(&info->print);
		return (0);
	}
	printf("%ld %d %s", (gettime() - info->time_start), philo->id, str);
	pthread_mutex_unlock(&info->print);
	return (1);
}

int	ft_eat(t_philo *philo)
{
	t_info		*info;

	if (!check_die())
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

void take_fork(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->fork_right);
		ft_print(philo, "has taken a fork\n");
		pthread_mutex_lock(&philo->fork_left);
		ft_print(philo, "has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(&philo->fork_left);
		ft_print(philo, "has taken a fork\n");
		pthread_mutex_lock(philo->fork_right);
		ft_print(philo, "has taken a fork\n");
	}
}

void	*ft_routine(void *data)
{
	t_philo		*philo;
	t_info		*info;

	info = starton();
	philo = (t_philo *)data;
	if (info->nb_philo == 1)
	{
		ft_print(philo, "has taken a fork\n");
		usleep_(info->limit_die);
		ft_print(philo, "died\n");
		return (NULL);
	}
	if (philo->id % 2 && info->nb_philo < 100)
		usleep(info->eat_time * 500);
	else if (philo->id % 2 && info->nb_philo >= 100)
		usleep(info->eat_time * 800);
	while (check_die())
	{
		take_fork(philo);
		ft_eat(philo);
		pthread_mutex_unlock(&philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		ft_sleep_and_think(philo);

	}
	return (NULL);
}

void dead_unlock(t_philo *philo, int i)
{
	t_info		*info;

	info = starton();
	pthread_mutex_unlock(&philo[i].lock);
	pthread_mutex_lock(&info->mutex_dead);
	info->die = 0;
	pthread_mutex_unlock(&info->mutex_dead);
	ft_print(&philo[i], "died\n");

}

int check_philo_eat_count(t_philo *philo)
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

int check_dead_philo(t_philo *philo)
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
			if (gettime() - info->time_start - philo[i].last_eat >= info->limit_die)
				return (dead_unlock(philo, i), 0);
			pthread_mutex_unlock(&philo[i].lock);
			if (check_philo_eat_count(philo) == 1)
			{
				pthread_mutex_lock(&info->mutex_dead);
				info->die = 0;
				pthread_mutex_unlock(&info->mutex_dead);
			}
		}
		usleep(2000);
	}
	return (0);
}

void	ft_init_philo(t_philo *philo, t_info *info, char **argv, int argc)
{
	int	i;

	i = 0;
	if (!ft_parsing(argv))
	{
		free(philo);
		exit(0);
	}
	ft_init_info(info, argc, argv);
	info->nb_philo = ft_atoi(argv[1]);
	i = 0;
	while (i < info->nb_philo - 1)
	{
		philo[i].fork_right = &philo[i + 1].fork_left;
		i++;
	}
	philo[i].fork_right = &philo[0].fork_left;
	i = 0;
	while (i < info->nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].last_eat = 0;
		philo[i].eat_count = info->need_eat;
		i++;
	}
	i = 0;
	while (i < info->nb_philo)
	{
		pthread_mutex_init(&philo[i].ceat, NULL);
		pthread_mutex_init(&philo[i].test, NULL);
		pthread_mutex_init(&philo[i].fork_left, NULL);
		pthread_mutex_init(&philo[i].lock, NULL);
		i++;
	}
	pthread_mutex_init(&info->eat_count, NULL);
	pthread_mutex_init(&info->shield, NULL);
	pthread_mutex_init(&info->print, NULL);
	pthread_mutex_init(&info->mutex_dead, NULL);
	i = 0;
	info->time_start = gettime();
	while (i < info->nb_philo)
	{
		pthread_create(&philo[i].tid, NULL, ft_routine, &philo[i]);
		i++;
	}
	if (info->nb_philo > 1)
		check_dead_philo(philo);
	i = 0;
	while (i < info->nb_philo)
	{
		pthread_join(philo[i].tid, NULL);
		i++;
	}
	i = 0;
	while (i < info->nb_philo)
	{
		pthread_mutex_destroy(&philo[i].fork_left);
		i++;
	}
	pthread_mutex_destroy(&info->shield);
	pthread_mutex_destroy(&info->print);
	pthread_mutex_destroy(&info->mutex_dead);
}



int	main(int argc, char **argv)
{
	static t_philo	*philo = NULL;
	t_info			*info;

	info = starton();
	if (argc == 5 || argc == 6)
	{
		if (ft_atoi(argv[1]) < 0)
		{
			printf("Error : number of philo must be positive\n");
			return (0);
		}
		philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
		if (!philo || !info)
			return (0);
		ft_init_philo(philo, info, argv, argc);
		free(philo);
	}
	else
	{
		printf("./philo [philo_nb] [time_die] [time_eat] [time_sleep]");
		printf(" [optional : must_eat]\n");
	}
	return (0);
}
