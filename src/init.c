/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:07:48 by pjurdana          #+#    #+#             */
/*   Updated: 2025/03/07 10:43:44 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


t_data	*ft_init(char **argv, t_data *data)
{
	int i;

	i = 0;
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->philos = malloc(sizeof(t_philo) * (ft_atoi(argv[1])));
	if (!data->philos)
	{
		free (data);
		return (NULL);
	}
	while (i < ft_atoi(argv[1]))
	{
		data->philos[i].rank = i + 1;
		
		printf("%d\n", data->philos[i].rank);

		data->philos[i].nb_philos = (ft_atoi(argv[1]));
		data->philos[i].time_to_die = (ft_atoi(argv[2]));
		data->philos[i].time_to_eat = (ft_atoi(argv[3]));
		data->philos[i].time_to_sleep = (ft_atoi(argv[4]));
		if (argv[5])
			data->philos->meals_eaten = (ft_atoi(argv[5]));
		// else
			// ????
		data->philos[i].eating = 0;
		data->philos[i].meals_eaten = 0;
		data->philos[i].dead = 0;
		data->philos[i].last_meal = 0;
//		data->philos[i].start_time = get_time_machin_ui;
		// data->philos[i].
		
		// last meal
		// start_time
		
		// l_fork // gives one of them to the philo and function for
		// r_fork // the other one or mutex lock i don't know for now
		
		// dead_lock // MUTEX i guess
		// meal_lock // MUTEX i guess
		// write_lock// MUTEX i guess
		// 
		
		i++;


	}
	// if (ft_init_philo(data) != 0)
	// {
	// 	free (data->philos);
	// 	free (data);
	// }
	return (data);
}


void	*routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;


	int i = 0;


	// printf("Philosophe : %d debut routine\n", philo->nb_philos);

	// usleep(500000);

	// printf("Philosophe : %d fin routine\n", philo->nb_philos);

	

	
	printf("Philosophe : %d debut routine\n", philo->rank);

	usleep(500000);

	printf("Philosophe : %d fin routine\n", philo->rank);


	

	printf("Philosophe : %d debut routine\n", (*philo).rank);

	usleep(500000);

	printf("Philosophe : %d fin routine\n", (*philo).rank);



	
	printf("Philosophe : %lu debut routine\n", philo[i].thread);

	usleep(500000);

	printf("Philosophe : %lu fin routine\n", philo[i].thread);


	
	// i++;
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
			printf("that's fuckep up son");
			exit(EXIT_FAILURE);
		}
		sleep (2);
		printf("\n\n%d\n\n", i);
		i++;
	}
	i = 0;
	while (i < data->philos[0].nb_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}