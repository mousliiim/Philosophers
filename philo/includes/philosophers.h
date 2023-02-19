/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:32:40 by mmourdal          #+#    #+#             */
/*   Updated: 2023/02/19 23:29:25 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# ifndef BENCH
#  define BENCH 0
# endif

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# define BRED "\e[1;91m"
# define END "\033[0m"
# define INT_MIN -2147483648
# define INT_MAX 2147483647

typedef struct s_philo
{
	int				id;
	pthread_t		tid;
	int				last_eat;
	int				eat_count;
	pthread_mutex_t	fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	lock;
	pthread_mutex_t	ceat;
}	t_philo;

typedef struct s_info
{
	int				die;
	int				nb_philo;
	long int		time_start;
	int				limit_die;
	int				eat_time;
	int				sleep_time;
	int				need_eat;
	pthread_mutex_t	mutex_dead;
	pthread_mutex_t	print;
	pthread_mutex_t	shield;
}	t_info;

/*------ ROUTINE_STOP.c ------*/
int			check_die(void);
void		dead_unlock(t_philo *philo, int i);
int			check_philo_eat_count(t_philo *philo);
int			check_dead_philo(t_philo *philo);

/*------ ROUTINE_ACTION.c ------*/
int			ft_eat(t_philo *philo);
int			ft_sleep_and_think(t_philo *philo);
void		take_fork(t_philo *philo);
int			ft_print(t_philo *philo, char *str);

/*------ UTILS.c ------*/
int			ft_atoi(const char *nptr);
void		ft_display(t_info *info);
int			ft_isdigit(int c, int param);
long int	gettime(void);
int			usleep_(long int duration);

/*------ UTILS_SECOND.c ------*/
int			ft_parsing(char **argv);
t_info		*starton(void);
void		ft_destroy_mutex(t_philo *philo, t_info *info);
#endif