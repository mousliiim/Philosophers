/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:30:57 by mmourdal          #+#    #+#             */
/*   Updated: 2023/02/16 03:57:39 by mmourdal         ###   ########.fr       */
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

void	ft_print(t_philo *philo, char *str)
{
	t_info		*info;

	info = starton();
	pthread_mutex_lock(&info->print);
	printf("%ld %d %s", (gettime() - info->time_start), philo->id, str);
	pthread_mutex_unlock(&info->print);
}

void ft_eat(t_philo *philo)
{
	t_info		*info;

	if (check_die() == 0)
		return ;
	info = starton();
	philo->last_eat = gettime() - info->time_start;
	ft_print(philo, "is eating\n");
	usleep_(info->eat_time);
}

void ft_sleep_and_think(t_philo *philo)
{
	t_info		*info;

	if (check_die() == 0)
		return ;
	info = starton();
	ft_print(philo, "is sleeping\n");
	usleep_(info->sleep_time);
	if (check_die() == 0)
		return ;
	ft_print(philo, "is thinking\n");
	if (philo->id % 2)
	{
		if (info->eat_time > info->sleep_time)
			usleep(info->eat_time - info->sleep_time);
		usleep(500);
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
		printf("%ld %d has taken a fork\n", (gettime() - info->time_start), philo->id);
		usleep_(info->limit_die);
		printf("%ld %d died\n", (gettime() - info->time_start), philo->id);
		return (NULL);
	}
	if (!(philo->id % 2))
		usleep(info->eat_time * 100);
	while (check_die())
	{
		if (philo->id % 2)
			pthread_mutex_lock(&philo->fork_left);
		else
			pthread_mutex_lock(philo->fork_right);
		if (check_die() == 0)
			return (NULL);
		ft_print(philo, "has taken a fork\n");
		if (philo->id % 2)
			pthread_mutex_lock(philo->fork_right);
		else
			pthread_mutex_lock(&philo->fork_left);
		if (check_die() == 0)
			return (NULL);
		ft_print(philo, "has taken a fork\n");
		ft_eat(philo);
		pthread_mutex_unlock(&philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		ft_sleep_and_think(philo);

	}
	return (NULL);
}

int check_dead_philo(t_philo *philo)
{
	t_info		*info;
	int			i;

	info = starton();
	i = 0;
	while (info->die)
	{
		i = 0;
		while (i < info->nb_philo)
		{
			if (gettime() - info->time_start - philo[i].last_eat >= info->limit_die)
			{
				pthread_mutex_lock(&info->mutex_dead);
				info->die = 0;
				if (info->nb_philo != 1)
					ft_print(&philo[i], "died\n");
				pthread_mutex_unlock(&info->mutex_dead);
				return (0);
			}
			i++;
		}
		usleep(1000);
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
		i++;
	}
	// ft_display(philo, info);
	i = 0;
	while (i < info->nb_philo)
	{
		pthread_mutex_init(&philo[i].fork_left, NULL);
		i++;
	}
	pthread_mutex_init(&info->mutex_dead, NULL);
	pthread_mutex_init(&info->print, NULL);
	i = 0;
	info->time_start = gettime();
	while (i < info->nb_philo)
	{
		pthread_create(&philo[i].tid, NULL, ft_routine, &philo[i]);
		i++;
	}
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
		pthread_mutex_destroy(&info->print);
		i++;
	}
	// Comment savoir si le mutex est lock ou unlock ? sans utiliser mutex_trylock :
	// pthread_mutex_t mutex;
	// mutex.__data.__lock;
}

int	main(int argc, char **argv)
{
	static t_philo	*philo = NULL;
	t_info			*info;

	info = starton();
	if (argc == 5 || argc == 6)
	{
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
