/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:07:48 by pjurdana          #+#    #+#             */
/*   Updated: 2025/03/17 13:00:47 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_args(t_philo *philos, char ** argv)
{
	philos->nb_philos = (ft_atoi(argv[1]));

	philos->time_to_die = (ft_atoi(argv[2]));
	philos->time_to_eat = (ft_atoi(argv[3]));
	philos->time_to_sleep = (ft_atoi(argv[4]));
	if (philos->nb_philos == -1 || philos->time_to_die == -1 || philos->time_to_eat == -1)
		return (-1);
	if (argv[5] && ft_atoi(argv[5]) > 0)
		philos->num_times_to_eat = (ft_atoi(argv[5]));
	else
		philos->num_times_to_eat = -1;

	return (0);
}

int	init_philos(char **argv, t_data *data, t_philo *philos, pthread_mutex_t *forks)
{
	int i;

	i = -1;
	while (++i < ft_atoi(argv[1]))
	{
		if (init_args(&philos[i], argv) == -1)
			return (-1);
		philos[i].dead_lock = &data->dead_lock;
		philos[i].meal_lock = &data->meal_lock;
		philos[i].write_lock = &data->write_lock;
		philos[i].rank = i + 1;
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		philos[i].dead = &data->is_dead;
		philos[i].start_time = get_current_time();
		philos[i].last_meal = get_current_time();
		philos[i].r_fork = &forks[i];
		if (i == 0)
			philos[i].l_fork = &forks[philos[i].nb_philos - 1];
		else
			philos[i].l_fork = &forks[i - 1];
	}
	return (0);
}

void init_data(t_data *data, t_philo *philos)
{
	data->is_dead = 0;
	data->philos = philos;
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	pthread_mutex_init(&data->write_lock, NULL);
}

void	init_fork(pthread_mutex_t *forks, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}