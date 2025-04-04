/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:26:41 by pjurdana          #+#    #+#             */
/*   Updated: 2025/03/20 09:45:13 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				rank;
	int				eating;
	int				meals_eaten;
	int				nb_philos;
	int				num_times_to_eat;
	int				*dead;
	pthread_t		thread;
	time_t			last_meal;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			start_time;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*write_lock;
}	t_philo;

typedef struct s_data
{
	int				is_dead;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}	t_data;

////////////*utils.c////////////////
int		ft_atoi(const char *nptr);
time_t	get_current_time(void);
int		ft_usleep(size_t milliseconds, t_philo *philo);
void	free_all(t_data *data, pthread_mutex_t *forks);
void	eat_sleep_think_ftc(t_philo *philo);
void	take_fork_ftc(t_philo *philo);
void	put_forks_fct(t_philo *philo);
int		ft_strlen(char *str);

////////////*init.c////////////////
int		init_philos(char **argv, t_data *data, t_philo *philos,
			pthread_mutex_t *forks);
void	init_fork(pthread_mutex_t *forks, int nb_philo);
void	init_data(t_data *data, t_philo *philo);
int		init_args(t_philo *philos, char **argv);

////////////*routine.c////////////////
void	*routine(void *arg);
void	launch_thread(t_data *data);
void	sleeping_and_thinking(t_philo *philo);
void	is_thinking_ftc(t_philo	*philo);
void	eating(t_philo *philo);

////////////*monitor.c////////////////
void	philo_scribing(char *str, t_philo *philo, int rank);
void	*supervisor(void *arg);
int		check_death(void *arg);

#endif