/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 19:54:21 by mmourdal          #+#    #+#             */
/*   Updated: 2023/02/13 21:49:28 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_parsing(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		if (argv[i][0] == '\0')
		{
			write(2, "Error: Argument not be empty !\n", 31);
			return (0);
		}
		while (argv[i][j])
		{
			if (ft_atoi(&argv[i][j]) < 0 || !ft_isdigit(argv[i][j]) || (argv[i][0] == '+' && argv[i][1] == '+') || (argv[i][0] == '+' && argv[i][1] == '\0'))
			{
				write(2, "Error: Argument must be a positif number !\n", 43);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_atoi(const char *nptr)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	while ((*nptr >= 7 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + *nptr - '0';
		nptr++;
	}
	return (result * sign);
}

void	ft_display(t_philo *philo, t_info *info)
{
	int	i;

	i = 0;
	printf("\n");
	while (i < philo->nb_philo)
	{
		printf("****************************\n");
		printf("Philo Number for philo[%d] is : %d\n", i, philo[i].id);
		printf("****************************\n\n");
		i++;
	}
	printf("%s*******************************%s", BRED, END);
	printf("\n\t%s   Info ⏱️:%s\n\n", BRED, END);
	printf("%sNb of Philo : %d%s\n", BRED, philo->nb_philo, END);
	printf("%sLimit to Die : %ld Ms%s\n", BRED, info->limit_die, END);
	printf("%sLimit to Eat : %ld Ms%s\n", BRED, info->eat_time, END);
	printf("%sLimit Sleep Time : %ld Ms%s\n", BRED, info->sleep_time, END);
	printf("%sPhilo[s] need to eat : %d Time[s]%s\n", BRED, info->need_eat, END);
	printf("%sFork total on the table : %d%s\n", BRED, philo->nb_philo, END);
	printf("%s\n*******************************\n%s", BRED, END);
}

int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9') || c == '-' || c == '+')
		return (1);
	return (0);
}

long int	gettime(void)
{
	struct timeval	time;
	long int		time_in_ms;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	time_in_ms = ((time.tv_sec) * 1000 + (time.tv_usec) / 1000);
	return (time_in_ms);
}

int	usleep_(long int duration)
{
	long	begin;

	begin = gettime();
	while (gettime() - begin < duration)
		usleep(10);
	return (1);
}