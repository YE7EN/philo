/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:15:23 by quentin           #+#    #+#             */
/*   Updated: 2025/03/11 15:26:58 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"



void	*check_death(void *arg)
{
	t_philo	*philo;
	time_t	time;

	philo = (t_philo *)arg;

	while (1)
	{
		time = get_current_time();

		if (time - philo->last_meal > philo->time_to_die)
		{
			pthread_mutex_lock(philo->dead_lock);
			if (!philo->dead)
			{
				philo->dead = 1;
				philo_scribing("mort", philo, philo->rank);
			}
			pthread_mutex_unlock(philo->dead_lock);
			break ;
		}
	}
	return (NULL);
}





void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->r_fork);
	philo_scribing("took a fork", philo, philo->rank);

	//	si un seul philo ? secu ici ou autre part, plus tot peut etre ?

	pthread_mutex_lock(&philo->l_fork);
	philo_scribing("took a fork", philo, philo->rank);

	philo->last_meal = get_current_time();

	pthread_mutex_lock(&philo->meal_lock);
	philo_scribing("is eating", philo, philo->rank);
	usleep(philo->time_to_eat);

	philo->meals_eaten++; // probleme qui a mange ([i]) faire une while des philo avec un int qui s'incremente quand le philo i a tout manger et ils ont tous manger si le int atteint le nombre de repas demande dans le monitor I guess
	pthread_mutex_unlock(&philo->meal_lock);

	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(&philo->r_fork);
}


void	sleeping_and_thinking(t_philo *philo)
{
	philo_scribing("sleeping", philo, philo->rank);
	usleep(philo->time_to_sleep);
	philo_scribing("thinking", philo, philo->rank);
}


void	*routine(void *arg)
{

	t_philo *philo = (t_philo *)arg;
	pthread_t	death_thread;
	int	i;

	pthread_create(&death_thread, NULL, check_death, philo);

	i = 0;
	//pthread_mutex_init(&philo->meal_lock, NULL);

	
	if (philo->rank  % 2 == 0) 
		usleep(1000);

		
/////////////	VOID_EATING	////////////////////

	// pthread_mutex_lock(&philo->r_fork);
	// philo_scribing("took a fork", philo, philo->rank);
	
	// //	si un seul philo ? secu ici ou autre part, plus tot peut etre ?
	
	// pthread_mutex_lock(&philo->l_fork);
	// philo_scribing("took a fork", philo, philo->rank);

	// philo->last_meal = get_current_time();
	
	// pthread_mutex_lock(&philo->meal_lock);
	// philo_scribing("is eating", philo, philo->rank);
	// usleep(philo->time_to_eat);

	// philo->meals_eaten++; // probleme qui a mange ([i]) faire une while des philo avec un int qui s'incremente quand le philo i a tout manger et ils ont tous manger si le int atteint le nombre de repas demande dans le monitor I guess
	// pthread_mutex_unlock(&philo->meal_lock);

	// pthread_mutex_unlock(&philo->l_fork);
	// pthread_mutex_unlock(&philo->r_fork);


	eating(philo);


	sleeping_and_thinking(philo);
	
/////////////	VOID_SLEEPING_AND_THINKING	////////////////////

// usleep(philo->time_to_sleep);
// philo_scribing("sleeping", philo, philo->rank); // need mutex_lock printf
// philo_scribing("thinking", philo, philo->rank); // need mutex_lock printf
// c'est pour eviter les conflits des fouchettes au debut du programme,
// si ca va trop vite ils prennent tous une fourchette
// et donc personne peut manger et tout le monde meurs
// on peut faire sur les impairs comme tu preferes
// routine dans une while de verif peut etre ?
	//while
		// eat
		// sleep
		// think
// 		printf("Philosophe : %d debut routine\n", philo->rank);
// 		// pthread_mutex_lock(&philo->write_lock);
// 		//printf("\ni :%d\n", i);
// 		usleep(500000);
// 		// pthread_mutex_unlock(&philo->write_lock);
// 		printf("Philosophe : %d fin routine\n", philo->rank);
// 	}
// 	i++;
	// pthread_mutex_unlock(&philo->meal_lock);
	return (NULL);
}






void	launch_thread(t_data *data)
{

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
	while (i < data->philos[0].nb_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	// pthread_attr_destroy(&data->philos->write_lock);
}
