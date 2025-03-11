/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:07:48 by pjurdana          #+#    #+#             */
/*   Updated: 2025/03/11 15:25:10 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_malloc_struct(char **argv, t_data **data, int nb_philo)
{
	(*data) = malloc(sizeof(t_data));
	if (!(*data))
		return (-1);
	(*data)->philos = malloc(sizeof(t_philo) * (nb_philo));
	if (!(*data)->philos)
	{
		free (data);
		return (-1);
	}
}
int	init_args(t_data **data, char ** argv)
{
	(*data)->philos->nb_philos = (ft_atoi(argv[1]));
	(*data)->philos->time_to_die = (ft_atoi(argv[2]));
	(*data)->philos->time_to_eat = (ft_atoi(argv[3]));
	(*data)->philos->time_to_sleep = (ft_atoi(argv[4]));
	if ((*data)->philos->nb_philos == -1 || (*data)->philos->time_to_die == -1 ||
		(*data)->philos->time_to_eat == -1 || (*data)->philos->time_to_sleep == -1 ||
		(*data)->philos->num_times_to_eat == -1)
		{
			free ((*data)->philos);
			free (*data);
			return (-1);
		}
	if (argv[5])
		(*data)->philos->num_times_to_eat = (ft_atoi(argv[5]));
	else
		(*data)->philos->num_times_to_eat = -1;
	
	return (0);
}

int	init_philos(char **argv, t_data **data, pthread_mutex_t *forks)
{	
	int i;
	
	i = -1;
	if (init_malloc_struct(argv, data, ft_atoi(argv[1])) == -1)
		return (-1);
	while (++i < ft_atoi(argv[1]))
	{
		if (init_args(data, argv) == -1)
			return (-1);
		(*data)->philos[i].dead = (*data)->is_dead;
		(*data)->philos[i].dead_lock = &(*data)->dead_lock;
		(*data)->philos[i].meal_lock = &(*data)->meal_lock;
		(*data)->philos[i].write_lock = &(*data)->write_lock;
		(*data)->philos[i].eating = 0;
		(*data)->philos[i].dead = &(*data)->is_dead;
		(*data)->philos[i].last_meal = get_crurrent_time();
		(*data)->philos[i].start_time = get_current_time();
		(*data)->philos[i].l_fork = &forks[i];
		if (i == 0)
			(*data)->philos[i].r_fork = &forks[ft_atoi(argv[1])];
		else
			(*data)->philos[i].r_fork = &forks[i - 1];
	}
	return (0);
}

void init_data(t_data ** data, t_philo *philo)
{
	(*data)->is_dead = 0;
	pthread_mutex_init(&(*data)->dead_lock, NULL);
	
	pthread_mutex_init(&(*data)->meal_lock, NULL);
	pthread_mutex_init(&(*data)->write_lock, NULL);
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