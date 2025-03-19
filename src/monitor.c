/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:25:31 by quentin           #+#    #+#             */
/*   Updated: 2025/03/19 12:42:59 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_scribing(char *str, t_philo *philo, int rank)
{
	time_t time;

	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 0)
	{
		pthread_mutex_lock(philo->write_lock);
		time = get_current_time() - philo->start_time;
		printf("%ld %d %s\n", time, rank, str);
		pthread_mutex_unlock(philo->write_lock);
	}
	// else
	// {
	// 	pthread_mutex_lock(philo->write_lock);
	// 	time = get_current_time() - philo->start_time;
	// 	printf("%ld %d %s\n", time, rank, str);
	// 	//pthread_mutex_unlock(philo->write_lock);
	// }
	pthread_mutex_unlock(philo->dead_lock);
}

int	check_if_all_eaten(void *arg)
{
	t_data	*data;
	int		i;
	int		for_all;

	i = 0;
	data = (t_data *) arg;
	for_all = 0;
	while (i < data->philos->nb_philos)
	{
		pthread_mutex_lock(data->philos[i].meal_lock);
		if (data->philos[i].meals_eaten >= data->philos->num_times_to_eat && data->philos->num_times_to_eat > 0)
		{
				for_all++;
		}
		pthread_mutex_unlock(&data->meal_lock);
		if (for_all == data->philos->nb_philos)
		{
			pthread_mutex_lock(&data->dead_lock);
			(data->is_dead = 1);
			pthread_mutex_unlock(&data->dead_lock);
			return (1);
		}
		i++;
	}
	//pthread_mutex_unlock(philo[i].meal_lock);
	return (0);
}
int	check_death(void *arg)
{
	t_data	*data;
	time_t	time;
	int	i;

	i = 0;
	data = (t_data *)arg;

		i = 0;

	while (i < data->philos->nb_philos)
	{
		time = get_current_time();
		pthread_mutex_lock(&data->meal_lock);
		if (time - data->philos[i].last_meal >= data->philos[i].time_to_die)
		{
			pthread_mutex_unlock(&data->meal_lock);
			pthread_mutex_lock(data->philos->dead_lock);
			(data->is_dead = 1);
			pthread_mutex_unlock(data->philos->dead_lock);
			pthread_mutex_lock(&data->write_lock);
			printf("%ld, %d, died\n", get_current_time() - data->philos->start_time, data->philos[i].rank);
			pthread_mutex_unlock(&data->write_lock);
			break ;
		}
		pthread_mutex_unlock(&data->meal_lock);
		usleep(1);
		i++;
	}
	pthread_mutex_lock(&data->dead_lock);
	if (data->is_dead == 1)
	{
		pthread_mutex_unlock(&data->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->dead_lock);
	return (0);
}


void	*supervisor(void *arg)
{
	t_data *data;

	data = (t_data *) arg;
	while (1)
	{
		// pthread_mutex_lock(data->philos->dead_lock);
		if (check_death(data) == 1 || check_if_all_eaten(data) == 1)
		{
			// pthread_mutex_unlock(data->philos->dead_lock);
			usleep(1);
			break;
		}
		usleep(1);
		// pthread_mutex_unlock(data->philos->dead_lock);
	}
	return (arg);
}