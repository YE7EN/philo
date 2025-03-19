/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:53:58 by quentin           #+#    #+#             */
/*   Updated: 2025/03/19 12:55:52 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

time_t	get_current_time(void)
{
	struct timeval	time;
	time_t			current_time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "error in gettimeofday process\n", 31);
	current_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (current_time);
}

int	ft_atoi(const char *nptr)
{
	int	res;

	res = 0;
	while (*nptr)
	{
		if (*nptr < '0' || *nptr > '9')
		{
			printf("Error\nBad args detected\n");
			return (-1);
		}
		res = res * 10 + (*nptr - '0');
		nptr++;
	}
	return (res);
}

void	free_all(t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->dead_lock);
	while (i < data->philos->nb_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

int	ft_usleep(size_t milliseconds, t_philo *philo)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
	{
		pthread_mutex_lock(philo->dead_lock);
		if (*(philo)->dead == 1)
		{
			pthread_mutex_unlock(philo->dead_lock);
			break;
		}
		pthread_mutex_unlock(philo->dead_lock);
		usleep(1);
	}
	return (0);
}
