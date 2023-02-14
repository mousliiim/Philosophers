/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:32:40 by mmourdal          #+#    #+#             */
/*   Updated: 2023/02/14 06:16:47 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# define GREEN "\033[0;32m"
# define RED "\033[5;31m"
# define END "\033[0m"
# define BRED "\e[1;91m"
# define TRUE 1
# define FALSE 0
# define INT_MIN -2147483648
# define INT_MAX 2147483647

typedef enum e_mode
{
	THINK,
	EAT,
	SLEEP,
	DIE,
	FORK,
}	t_mode;

typedef struct s_time
{
	long int	sec;
	long int	usec;
}	t_time;

// Ajouter un mutex pour chaque printf pour eviter les conflits d'ecriture entre les threads dans la structure t_philo
// Ajouter un mutex aussi pour chaque gettime pour eviter les conflits d'ecriture entre les threads dans la structure t_philo
typedef struct s_philo
{
	int				id;
	pthread_t		tid;
	int				nb_philo;
	int				count;
	long int		last_eat;
	pthread_mutex_t	fork_left;
	pthread_mutex_t	*fork_right;
}	t_philo;

typedef struct s_info
{
	long int	time_start;
	long int	limit_die;
	long int	eat_time;
	long int	sleep_time;
	int			need_eat;
	pthread_mutex_t	print;
	pthread_mutex_t	time;
}	t_info;

int			ft_atoi(const char *nptr);
void		ft_display(t_philo *philo, t_info *info);
int			ft_isdigit(int c);
int			ft_parsing(char **argv);
int			usleep_(long int duration);
long int	gettime(void);
#endif