/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:30:57 by mmourdal          #+#    #+#             */
/*   Updated: 2023/02/19 23:09:12 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	ft_init_struct_info(t_info *info, int argc, char **argv)
{
	info->limit_die = ft_atoi(argv[2]);
	info->eat_time = ft_atoi(argv[3]);
	info->sleep_time = ft_atoi(argv[4]);
	info->die = 1;
	if (argc == 6)
		info->need_eat = ft_atoi(argv[5]);
	else
		info->need_eat = -1;
	info->nb_philo = ft_atoi(argv[1]);
}

static void	ft_init_struct_thread(t_philo *philo, t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->nb_philo - 1)
		philo[i].fork_right = &philo[i + 1].fork_left;
	philo[i].fork_right = &philo[0].fork_left;
	i = -1;
	while (++i < info->nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].last_eat = 0;
		philo[i].eat_count = info->need_eat;
	}
	i = -1;
	while (++i < info->nb_philo)
	{
		pthread_mutex_init(&philo[i].ceat, NULL);
		pthread_mutex_init(&philo[i].fork_left, NULL);
		pthread_mutex_init(&philo[i].lock, NULL);
	}
	pthread_mutex_init(&info->shield, NULL);
	pthread_mutex_init(&info->print, NULL);
	pthread_mutex_init(&info->mutex_dead, NULL);
}

static void	*ft_routine(void *data)
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
	if (philo->id % 2)
		usleep(info->eat_time * 500);
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

static void	ft_init_philo(t_philo *philo, t_info *info, char **argv, int argc)
{
	int	i;

	if (!ft_parsing(argv))
	{
		free(philo);
		exit(0);
	}
	ft_init_struct_info(info, argc, argv);
	ft_init_struct_thread(philo, info);
	if (BENCH == 1)
		ft_display(info);
	i = -1;
	info->time_start = gettime();
	while (++i < info->nb_philo)
		pthread_create(&philo[i].tid, NULL, ft_routine, &philo[i]);
	if (info->nb_philo > 1)
		check_dead_philo(philo);
	i = -1;
	while (++i < info->nb_philo)
		pthread_join(philo[i].tid, NULL);
	ft_destroy_mutex(philo, info);
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
