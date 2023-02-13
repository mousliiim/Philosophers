/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:30:57 by mmourdal          #+#    #+#             */
/*   Updated: 2023/02/13 05:53:50 by mmourdal         ###   ########.fr       */
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
	if (argc == 6)
		info->need_eat = ft_atoi(argv[5]);
	else
		info->need_eat = 0;
}

// Ajouter un mutex pour chaque printf pour eviter les conflits d'ecriture entre les threads dans la structure t_philo
// Ajouter un mutex aussi pour chaque gettime pour eviter les conflits d'ecriture entre les threads dans la structure t_philo

void	*ft_routine(void *data)
{
	t_philo		*philo;
	t_info		*info;

	info = starton();
	philo = (t_philo *)data;
	if (philo->nb_philo == 1)
	{
		printf("%ld %d has taken a fork\n", (gettime() - info->time_start), philo->id);
		usleep_(info->limit_die);
		printf("%ld %d is died\n", (gettime() - info->time_start), philo->id);
		return (NULL);
	}
	if (!(philo->id % 2))
		usleep_(info->eat_time);
	while (TRUE)
	{
		philo->count = 0;
		pthread_mutex_lock(&philo->fork_left);
		printf("%ld %d has taken a fork\n", (gettime() - info->time_start), philo->id);
		pthread_mutex_lock(philo->fork_right);
		printf("%ld %d has taken a fork\n", (gettime() - info->time_start), philo->id);
		printf("%ld %d is eating\n", (gettime() - info->time_start), philo->id);
		philo->last_eat = gettime() - info->time_start;
		usleep_(info->eat_time);
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(&philo->fork_left);
		printf("%ld %d is sleeping\n", (gettime() - info->time_start), philo->id);
		usleep_(info->sleep_time);
		printf("%ld %d is thinking\n", (gettime() - info->time_start), philo->id);
	}
	return (NULL);
}

void	ft_init_philo(t_philo *philo, t_info *info, char **argv, int argc)
{
	int	i;

	i = 0;
	if (!ft_parsing(argv))
		exit(0);
	ft_init_info(info, argc, argv);
	philo->nb_philo = ft_atoi(argv[1]);
	i = 0;
	while (i < philo->nb_philo - 1)
	{
		philo[i].fork_right = &philo[i + 1].fork_left;
		i++;
	}
	philo[i].fork_right = &philo[0].fork_left;
	i = 0;
	while (i < philo->nb_philo)
	{
		philo[i].nb_philo = ft_atoi(argv[1]);
		philo[i].id = i + 1;
		i++;
	}
	// ft_display(philo, info);
	i = 0;
	while (i < philo->nb_philo)
	{
		pthread_mutex_init(&philo[i].fork_left, NULL);
		i++;
	}
	i = 0;
	// printf("Le temps start UNIX en millisecondes est : %ld Ms\n", info->time_start);
	// usleep_(500);
	// printf("Le temps en millisecondes est entre le premier start et celui la est de : %ld Ms\n", (gettime() - info->time_start));
	info->time_start = gettime();
	while (i < philo->nb_philo)
	{
		pthread_create(&philo[i].tid, NULL, ft_routine, &philo[i]);
		i++;
	}
	i = 0;
	while (i < philo->nb_philo)
	{
		pthread_join(philo[i].tid, NULL);
		i++;
	}
	i = 0;
	while (i < philo->nb_philo)
	{
		pthread_mutex_destroy(&philo[i].fork_left);
		i++;
	}

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
	}
	else
	{
		printf("./philo [philo_nb] [time_die] [time_eat] [time_sleep]");
		printf(" [optional : must_eat]\n");
	}
	return (0);
}
