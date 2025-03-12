/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:15:23 by quentin           #+#    #+#             */
/*   Updated: 2025/03/12 12:44:57 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	philo_scribing("took the right fork 🔱​", philo, philo->rank);

	//	si un seul philo ? secu ici ou autre part, plus tot peut etre ?

	pthread_mutex_lock(philo->l_fork);
	philo_scribing("took the left fork 🔱​", philo, philo->rank);

	philo->last_meal = get_current_time();

	pthread_mutex_lock(philo->meal_lock);
	philo_scribing("is eating 😋​", philo, philo->rank);
	usleep(philo->time_to_eat);

	philo->meals_eaten++; // probleme qui a mange ([i]) faire une while des philo avec un int qui s'incremente quand le philo i a tout manger et ils ont tous manger si le int atteint le nombre de repas demande dans le monitor I guess
	pthread_mutex_unlock(philo->meal_lock);

	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	sleeping_and_thinking(t_philo *philo)
{
	philo_scribing("sleeping 😴​", philo, philo->rank);
	usleep(philo->time_to_sleep);
	philo_scribing("thinking 🤔​", philo, philo->rank);
}

void	*routine(void *arg)
{

	t_philo *philo = (t_philo *)arg;
	//int	i;
	
	
	
	//i = 0;
	//pthread_mutex_init(&philo->meal_lock, NULL);
	
	
	if (philo->rank  % 2 == 0) 
		usleep(1000);
	// while (1)
	// {

		if (*philo->dead == 1)
			exit(EXIT_FAILURE);

		eating(philo);

		sleeping_and_thinking(philo);
	// }
return (NULL);
}






void	launch_thread(t_data *data)
{
	
	
	pthread_t	death_thread;
	
	pthread_create(&death_thread, NULL, check_death, data->philos);
	
	
	int i;

	i = 0;
	while (i < data->philos->nb_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &routine, &data->philos[i]) != 0)
		{
			printf("that's fuckep up son <--- Pardon ? xD\n");
			exit(EXIT_FAILURE);
		}
		sleep (2);
		//printf("\n\n%d\n\n", i);
		i++;
	}
	i = 0;
	pthread_join(death_thread, NULL);
	
	while (i < data->philos[0].nb_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	// pthread_attr_destroy(&data->philos->write_lock);
}
