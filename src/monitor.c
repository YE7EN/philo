/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:25:31 by quentin           #+#    #+#             */
/*   Updated: 2025/03/12 18:06:28 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"









void	philo_scribing(char *str, t_philo *philo, int rank)
{
	time_t time;

	pthread_mutex_lock(philo->write_lock);

	time = get_current_time() - philo->start_time;

	// printf("%ld %d %s", time, rank, str);



	// rank++;


	printf("\n%ld | %d | %s\n", time, rank, str);


	pthread_mutex_unlock(philo->write_lock);


}

int	check_death(void *arg)
{
	t_philo	*philo;
	time_t	time;
	int	i;

	i = 0;
	philo = (t_philo *)arg;

	while (1)
	{
		i = 0;
		while (i < philo->nb_philos)
		{
			time = get_current_time();
			
			pthread_mutex_lock(philo[i].meal_lock);
			
			if (time - philo[i].last_meal >= philo[i].time_to_die)
			{
				pthread_mutex_lock(philo[i].dead_lock);

					printf("\n\n\nHALLO JE SUIS MORT OU PAS ???\n\n\n");
					(*philo[i].dead = 1);
					philo_scribing("mort", philo, philo[i].rank);

				pthread_mutex_unlock(philo[i].dead_lock);
				break ;
			}
			
			pthread_mutex_unlock(philo[i].meal_lock);

			usleep(500);
			i++;
		}
		if (*philo->dead == 1)
			exit(EXIT_FAILURE);
	}
	return (0);
}	

void	*supervisor(void *arg)
{
	t_philo *philos;

	philos = (t_philo *) arg;
	while (1)
	{
		if (check_death(philos) == 1)
			break;
	}
	return (arg);
}