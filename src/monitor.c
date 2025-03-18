/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:25:31 by quentin           #+#    #+#             */
/*   Updated: 2025/03/18 14:15:35 by qumiraud         ###   ########.fr       */
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
	else
	{
		pthread_mutex_lock(philo->write_lock);
		time = get_current_time() - philo->start_time;
		printf("%ld %d %s\n", time, rank, str);
		// pthread_mutex_unlock(philo->write_lock);
	}
	pthread_mutex_unlock(philo->dead_lock);
}

int	check_if_all_eaten(void *arg)
{
	t_philo	*philo;
	int		i;
	int		for_all;

	i = 0;
	philo = (t_philo *) arg;
	for_all = 0;
	while (i < philo->nb_philos)
	{
		pthread_mutex_lock(philo[i].meal_lock);
		if (philo[i].meals_eaten >= philo->num_times_to_eat && philo->num_times_to_eat > 0)
		{
				for_all++;
		}
		pthread_mutex_unlock(philo[i].meal_lock);
		if (for_all == philo->nb_philos)
		{
			pthread_mutex_lock(philo->dead_lock);
			(*philo[i].dead = 1);
			pthread_mutex_unlock(philo->dead_lock);
			philo->time_to_eat = 0;
			return (1);
		}
		i++;
	}
	//pthread_mutex_unlock(philo[i].meal_lock);
	return (0);
}
int	check_death(void *arg)
{
	t_philo	*philo;
	time_t	time;
	int	i;

	i = 0;
	philo = (t_philo *)arg;

		i = 0;

	while (i < philo->nb_philos)
	{
		time = get_current_time();

		pthread_mutex_lock(philo[i].meal_lock);

		if (time - philo[i].last_meal >= philo[i].time_to_die)
		{
			pthread_mutex_lock(philo->dead_lock);
			(*philo[i].dead = 1);
			pthread_mutex_unlock(philo->dead_lock);
			philo_scribing("mort 🪦​", philo, philo[i].rank);
			break ;
		}

			pthread_mutex_unlock(philo[i].meal_lock);
			usleep(5);
			i++;
	}
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}


void	*supervisor(void *arg)
{
	t_philo *philos;

	philos = (t_philo *) arg;
	while (1)
	{
		if (check_death(philos) == 1 || check_if_all_eaten(philos) == 1)
		{
			//printf("j'ai bien mange woulah\n\n\n");
			ft_usleep(500);
			break;
		}
	}
	return (arg);
}