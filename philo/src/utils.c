/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 19:54:21 by mmourdal          #+#    #+#             */
/*   Updated: 2023/02/19 23:16:04 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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
		if ((result * sign) > INT_MAX || (result * sign) < INT_MIN)
			return (-42);
		nptr++;
	}
	return (result * sign);
}

void	ft_display(t_info *info)
{
	printf("\n");
	printf("%s*******************************%s", BRED, END);
	printf("\n\t%s   Info ⏱️:%s\n\n", BRED, END);
	printf("%sNb of Philo : %d%s\n", BRED, info->nb_philo, END);
	printf("%sLimit to Die : %d Ms%s\n", BRED, info->limit_die, END);
	printf("%sLimit to Eat : %d Ms%s\n", BRED, info->eat_time, END);
	printf("%sLimit Sleep Time : %d Ms%s\n", BRED, info->sleep_time, END);
	printf("%sPhilo[s] need to eat : %d Time[s]%s\n", BRED, info->need_eat, END);
	printf("%sFork total on the table : %d%s\n", BRED, info->nb_philo, END);
	printf("%s\n*******************************\n%s", BRED, END);
}

int	ft_isdigit(int c, int param)
{
	if (param == 1)
	{
		if (c >= '0' && c <= '9')
			return (1);
	}
	else
	{
		if ((c >= '0' && c <= '9') || c == '+')
			return (1);
	}
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
