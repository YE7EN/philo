/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:15:23 by quentin           #+#    #+#             */
/*   Updated: 2025/03/18 14:16:18 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eating(t_philo *philo)
{
	if (philo->rank % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		philo_scribing("has taken a fork", philo, philo->rank);

		pthread_mutex_lock(philo->l_fork);
		philo_scribing("has taken a fork", philo, philo->rank);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		philo_scribing("has taken a fork", philo, philo->rank);

		pthread_mutex_lock(philo->r_fork);
		philo_scribing("has taken a fork", philo, philo->rank);
	}
	philo_scribing("is eating", philo, philo->rank);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++; // probleme qui a mange ([i]) faire une while des philo avec un int qui s'incremente quand le philo i a tout manger et ils ont tous manger si le int atteint le nombre de repas demande dans le monitor I guess
	pthread_mutex_unlock(philo->meal_lock);
	if (philo->time_to_eat != 0)
		ft_usleep(philo->time_to_eat);
	//pthread_mutex_lock(philo->meal_lock);
	//pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	is_thinking_ftc(t_philo	*philo)
{
	time_t	t_t_think;

	t_t_think = (philo->time_to_die - (get_current_time() - philo->last_meal) - philo->time_to_eat) / 2;
	if (t_t_think < 0)
		t_t_think = 0;
	if (t_t_think == 0)
		t_t_think = 1;
	if (t_t_think > 600)
		t_t_think = 200;
	usleep(t_t_think);
}

void	sleeping_and_thinking(t_philo *philo)
{
	philo_scribing("is sleeping", philo, philo->rank);
	ft_usleep(philo->time_to_sleep);

	philo_scribing("is thinking", philo, philo->rank);
	is_thinking_ftc(philo);
}

void	*routine(void *arg)
{

	t_philo *philo = (t_philo *)arg;

	if (philo->rank % 2 != 0)
		usleep(100);
	while (1)
	{
		eating(philo);
		sleeping_and_thinking(philo);
		pthread_mutex_lock(philo->dead_lock);
		if (*philo->dead == 1)
		{
			ft_usleep(500);
			break;
		}
		pthread_mutex_unlock(philo->dead_lock);
	}
	pthread_mutex_unlock(philo->write_lock);
	return (NULL);
}




#include <string.h>

void	launch_thread(t_data *data)
{


	pthread_t	death_thread;


	pthread_create(&death_thread, NULL, &supervisor, data->philos);

	// if (pthread_create(&death_thread, NULL, &supervisor, data->philos) != 0)
	// exit(EXIT_FAILURE);



	int i;

	i = 0;
	while (i < data->philos->nb_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &routine, &data->philos[i]) != 0)
		{
			exit(EXIT_FAILURE);
			printf("that's fuckep up son <--- Pardon ? xD\n");
		}
		i++;
		//printf("\n\n%d\n\n", i);
	}
	i = 0;
	pthread_join(death_thread, NULL);

	while (i < data->philos[0].nb_philos)
	{
		i++;
	}
	// pthread_attr_destroy(&data->philos->write_lock);
}
