/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:25:31 by quentin           #+#    #+#             */
/*   Updated: 2025/03/12 12:44:27 by quentin          ###   ########.fr       */
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
			// if (!philo->dead)
			// {
				printf("\n\n\nHALLO JE SUIS MORT OU PAS ???\n\n\n");
				return (*philo->dead = 1);
				philo_scribing("mort", philo, philo->rank);
				//ft_tread_and_exit(arg);
			// }
			pthread_mutex_unlock(philo->dead_lock);
			break ;
		}
	}
	return (NULL);
}