/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:26:41 by pjurdana          #+#    #+#             */
/*   Updated: 2025/03/07 10:11:15 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>




typedef struct	s_philo
{
	int				rank;
	int				eating;
	int				meals_eaten;
	int				nb_philos;
	int				num_times_to_eat;
	int				*dead;
	pthread_t		thread;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
}				t_philo;

typedef struct	s_data
{
	int				is_dead;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}				t_data;


int	ft_atoi(const char *nptr);



t_data	*ft_init(char **argv, t_data *data);
void	init_thread(t_data *data);






#endif