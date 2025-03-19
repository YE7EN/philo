/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:18:58 by qumiraud          #+#    #+#             */
/*   Updated: 2025/03/19 13:19:51 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eat_sleep_think_ftc(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*(philo)->dead == 0)
	{
		pthread_mutex_unlock(philo->dead_lock);
		eating(philo);
	}
	else
		pthread_mutex_unlock(philo->dead_lock);
	pthread_mutex_lock(philo->dead_lock);
	if (*(philo)->dead == 0)
	{
		pthread_mutex_unlock(philo->dead_lock);
		sleeping_and_thinking(philo);
	}
	else
		pthread_mutex_unlock(philo->dead_lock);
}
