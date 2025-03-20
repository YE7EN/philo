/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:18:58 by qumiraud          #+#    #+#             */
/*   Updated: 2025/03/20 10:28:58 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
		i++;
	return (i);
}

void	put_forks_fct(t_philo *philo)
{
	if (philo->rank % 2 == 0)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
}

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
