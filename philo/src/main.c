/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:30:57 by mmourdal          #+#    #+#             */
/*   Updated: 2023/02/07 18:41:59 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#define NC	"\e[0m"
#define YELLOW	"\e[1;33m"
#define TIMES_TO_COUNT 21000

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

typedef struct s_count
{
	unsigned int	count;
	pthread_mutex_t	mutex;
}	t_count;

void	*ft_increase(void *data)
{
	pthread_t	tid;
	t_count		*test;

	test = (t_count *)data;
	pthread_mutex_lock(&test->mutex);
	tid = pthread_self();
	pthread_mutex_unlock(&test->mutex);
	pthread_mutex_lock(&test->mutex);
	test->count++;
	printf("Thread : [ %lu ] | Count value start : %d\n", tid, test->count);
	pthread_mutex_unlock(&test->mutex);
	return (NULL);
}

int	main(void)
{
	pthread_t		thread_id1;
	pthread_t		thread_id2;
	t_count			test;

	pthread_mutex_init(&test.mutex, NULL);
	test.count = 0;
	pthread_create(&thread_id1, NULL, ft_increase, &test);
	pthread_create(&thread_id2, NULL, ft_increase, &test);
	pthread_join(thread_id1, NULL);
	pthread_join(thread_id2, NULL);
	return 0;
}
