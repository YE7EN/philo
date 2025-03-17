/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:15:23 by quentin           #+#    #+#             */
/*   Updated: 2025/03/13 16:46:47 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eating(t_philo *philo)
{
	// if (philo->rank % 2 == 0) {  // Pour certains philosophes, prendre d'abord la gauche
    //     pthread_mutex_lock(philo->l_fork);
    //     philo_scribing("took the left fork 🔱​", philo, philo->rank);
        
    //     pthread_mutex_lock(philo->r_fork);
    //     philo_scribing("took the right fork 🔱​", philo, philo->rank);
    // } else {  // Pour d'autres philosophes, prendre d'abord la droite
    //     pthread_mutex_lock(philo->r_fork);
    //     philo_scribing("took the right fork 🔱​", philo, philo->rank);
        
    //     pthread_mutex_lock(philo->l_fork);
    //     philo_scribing("took the left fork 🔱​", philo, philo->rank);
    // }
	////////////////////////////////////////
	if (philo->r_fork < philo->l_fork)
	{
		pthread_mutex_lock(philo->r_fork);
		philo_scribing("took the right fork 🔱​", philo, philo->rank);

		pthread_mutex_lock(philo->l_fork);
        philo_scribing("took the left fork 🔱​", philo, philo->rank);
    }
    else
    {
        pthread_mutex_lock(philo->l_fork);
        philo_scribing("took the left fork 🔱​", philo, philo->rank);

        pthread_mutex_lock(philo->r_fork);
        philo_scribing("took the right fork 🔱​", philo, philo->rank);
    }
	/////////////////////////////////////////
	// pthread_mutex_lock(philo->r_fork);
	// // printf("\nfork : %d\n", philo->rank);
	// philo_scribing("took the right fork 🔱​", philo, philo->rank);
	
	// pthread_mutex_lock(philo->l_fork);
	// // printf("\nfork : %d\n", philo->rank);
	// philo_scribing("took the left fork 🔱​", philo, philo->rank);
	
	philo_scribing("is eating 😋​", philo, philo->rank);

	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++; // probleme qui a mange ([i]) faire une while des philo avec un int qui s'incremente quand le philo i a tout manger et ils ont tous manger si le int atteint le nombre de repas demande dans le monitor I guess
	printf("\n\n%d\n\n", philo->meals_eaten);
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	sleeping_and_thinking(t_philo *philo)
{
	philo_scribing("sleeping 😴​", philo, philo->rank);
	ft_usleep(philo->time_to_sleep);

	philo_scribing("thinking 🤔​", philo, philo->rank);
}

void	*routine(void *arg)
{

	t_philo *philo = (t_philo *)arg;
	//int	i;
	
	
	
	//i = 0;
	//pthread_mutex_init(&philo->meal_lock, NULL);
	
	
	if (philo->rank % 2 == 0)
		usleep(1);
	while (1)
	{

		// if (*philo->dead == 1)
		// 	exit(EXIT_FAILURE);

		eating(philo);

		// if (*philo->dead == 1)
		// 	exit(EXIT_FAILURE);

		sleeping_and_thinking(philo);

		// if (*philo->dead == 1)
		// 	exit(EXIT_FAILURE);

	}
return (NULL);
}






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
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	// pthread_attr_destroy(&data->philos->write_lock);
}
