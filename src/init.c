/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:07:48 by pjurdana          #+#    #+#             */
/*   Updated: 2025/03/10 12:05:11 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_value(char **argv, t_data **data)
{	
	int i;
	int	nb_philo;
	
	i = 0;
	nb_philo = ft_atoi(argv[1]);
	if (nb_philo == -1)
		return (-1);
	(*data) = malloc(sizeof(t_data));
	if (!(*data))
		return (-1);
	(*data)->philos = malloc(sizeof(t_philo) * (nb_philo));
	if (!(*data)->philos)
	{
		free (data);
		return (-1);
	}
	while (i < nb_philo)
	{
		(*data)->philos[i].rank = i + 1;
		
		//printf("%d\n", (*data)->philos[i].rank);

		(*data)->philos[i].nb_philos = (nb_philo);
		(*data)->philos[i].time_to_die = (ft_atoi(argv[2]));
		(*data)->philos[i].time_to_eat = (ft_atoi(argv[3]));
		(*data)->philos[i].time_to_sleep = (ft_atoi(argv[4]));
		if (argv[5])
			(*data)->philos->meals_eaten = (ft_atoi(argv[5]));
		if ((*data)->philos[i].nb_philos == -1 || (*data)->philos[i].time_to_die == -1 ||
				(*data)->philos[i].time_to_eat == -1 || (*data)->philos[i].time_to_sleep == -1 ||
					(*data)->philos->meals_eaten == -1)
		{
			free ((*data)->philos);
			free (*data);
			return (-1);
		}
		// else
			// ????
		(*data)->philos[i].eating = 0;
		(*data)->philos[i].meals_eaten = 0;
		(*data)->philos[i].dead = 0;
		(*data)->philos[i].last_meal = 0;
//		data->philos[i].start_time = get_time_machin_ui;
		// data->philos[i].
		
		// last meal
		// start_time
		
		// l_fork // gives one of them to the philo and function for
		// r_fork // the other one or mutex lock i don't know for now
		

		
		// 
		
		i++;
		
		
	}
	pthread_mutex_init(&(*data)->philos->dead_lock, NULL);
	pthread_mutex_init(&(*data)->philos->meal_lock, NULL);
	pthread_mutex_init(&(*data)->philos->write_lock, NULL);
	// if (ft_init_philo(data) != 0)
	// {
	// 	free (data->philos);
	// 	free (data);
	// }
	return (0);
}


void	*routine(void *arg)
{

	t_philo *philo = (t_philo *)arg;
	int	i;

	i = 0;
	pthread_mutex_init(&philo->meal_lock, NULL);
	pthread_mutex_lock(&philo->meal_lock);

//	printf("%d : eating", philo->rank);
//	 miam je suis le philoe x et je mange mes morts

	//////oh les mains on ne touche plus a rien je vais push car je vais graille!!!!!!!!!!!!!!!!!!!

	pthread_mutex_unlock(&philo->meal_lock);

	//if (philo->rank  % 2 == 0) 
		//usleep(1000);
// c'est pour eviter les conflits des fouchettes au debut du programme,
// si ca va trop vite ils prennent tous une fourchette
// et donc personne peut manger et tout le monde meurs
// on peut faire sur les impairs comme tu preferes

// routine dans une while de verif peut etre ?
	//while
		// eat
		// sleep
		// think

	while (i == 0) // utiliser i pour verifier la mort d'un philo pour mettre fin ?
	{

//		i = eating(philo, i);

//		i = sleeping(philo, i);

//		i = thinking(philo, i);


		printf("Philosophe : %d debut routine\n", philo->rank);
		// pthread_mutex_lock(&philo->write_lock);
		//printf("\ni :%d\n", i);
		usleep(500000);
		// pthread_mutex_unlock(&philo->write_lock);
		printf("Philosophe : %d fin routine\n", philo->rank);
		
	}


	return (NULL);
}

void	init_thread(t_data *data)
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