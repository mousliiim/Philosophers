/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_second.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 23:15:37 by mmourdal          #+#    #+#             */
/*   Updated: 2023/02/19 23:31:22 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	ft_parsing_2(char **argv, int i, int j)
{
	while (argv[i][j])
	{
		if (ft_atoi(&argv[i][j]) == -42)
		{
			write(2, "Error: Maximum number allowed is INT_MAX!\n", 42);
			return (0);
		}
		if (ft_atoi(&argv[i][j]) < 0 || !ft_isdigit(argv[i][j], 2) ||
			(argv[i][0] == '+' && argv[i][1] == '\0') ||
			(argv[i][0] == '+' && argv[i][1] == '+') ||
			(argv[i][0] == '+' && ft_isdigit(argv[i][j], 1) &&
			argv[i][j + 1] == '+') || (ft_isdigit(argv[i][0], 1) &&
			argv[i][1] == '+'))
		{
			write(2, "Error: Need correct argument !\n", 31);
			return (0);
		}
		j++;
	}
	return (1);
}

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
		if (!ft_parsing_2(argv, i, j))
			return (0);
		if (argv[i][j - 1] == '+')
			return (0);
		i++;
	}
	return (1);
}

void	ft_destroy_mutex(t_philo *philo, t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->nb_philo)
	{
		pthread_mutex_destroy(&philo[i].ceat);
		pthread_mutex_destroy(&philo[i].fork_left);
		pthread_mutex_destroy(&philo[i].lock);
	}
	pthread_mutex_destroy(&info->shield);
	pthread_mutex_destroy(&info->print);
	pthread_mutex_destroy(&info->mutex_dead);
}

t_info	*starton(void)
{
	static t_info	info;

	return (&info);
}
