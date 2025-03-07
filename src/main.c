/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:26:35 by pjurdana          #+#    #+#             */
/*   Updated: 2025/03/07 10:10:24 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-')
	{
		printf("ERROR\nNo negative arguments allowed\n");
		exit (EXIT_FAILURE);
	}
	if (nptr[i] == '+')
	{
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	return (res * sign);
}

void	ft_verif_argv(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) == 0)
		{
			printf("ERROR\nWrong argument\n");
			exit (EXIT_FAILURE);
		}
		i++;
	}
}

void	ft_verif_argc(int argc)
{
	if (argc != 5 && argc != 6)
	{
		printf("ERROR\nWrong number of argument\n");
		exit (EXIT_FAILURE);
	}
}

// int	ft_init_philo(t_data *data)
// {
// 	int i;

// 	i = 0;
// 	while (i < data->philos->nb_philos)
// 	{
// 		data->philos[i].rank = i + 1;
// 		i++;
// 	}
// 	return (0);
// }



// t_data	*ft_init(char **argv, t_data *data)
// {
// 	int i;

// 	i = 0;
// 	data = malloc(sizeof(t_data));
// 	if (!data)
// 		return (NULL);
// 	data->philos = malloc(sizeof(t_philo) * (ft_atoi(argv[1])));
// 	if (!data->philos)
// 	{
// 		free (data);
// 		return (NULL);
// 	}
// 	while (i < ft_atoi(argv[1]))
// 	{
// 		data->philos[i].rank = i + 1;
		
// 		printf("%d\n", data->philos[i].rank);

// 		data->philos[i].nb_philos = (ft_atoi(argv[1]));
// 		data->philos[i].time_to_die = (ft_atoi(argv[2]));
// 		data->philos[i].time_to_eat = (ft_atoi(argv[3]));
// 		data->philos[i].time_to_sleep = (ft_atoi(argv[4]));
// 		if (argv[5])
// 			data->philos->meals_eaten = (ft_atoi(argv[5]));
// 		// else
// 			// ????
// 		data->philos[i].eating = 0;
// 		data->philos[i].meals_eaten = 0;
// 		data->philos[i].dead = 0;
// 		data->philos[i].last_meal = 0;
// //		data->philos[i].start_time = get_time_machin_ui;
// 		// data->philos[i].
		
// 		// last meal
// 		// start_time
		
// 		// l_fork // gives one of them to the philo and function for
// 		// r_fork // the other one or mutex lock i don't know for now
		
// 		// dead_lock // MUTEX i guess
// 		// meal_lock // MUTEX i guess
// 		// write_lock// MUTEX i guess
// 		// 
		
// 		i++;


// 	}
// 	// if (ft_init_philo(data) != 0)
// 	// {
// 	// 	free (data->philos);
// 	// 	free (data);
// 	// }
// 	return (data);
// }


// void	*routine(void *arg)
// {
// 	t_philo *philo = (t_philo *)arg;


// 	int i = 0;


// 	// printf("Philosophe : %d debut routine\n", philo->nb_philos);

// 	// usleep(500000);

// 	// printf("Philosophe : %d fin routine\n", philo->nb_philos);

	

	
// 	printf("Philosophe : %d debut routine\n", philo->rank);

// 	usleep(500000);

// 	printf("Philosophe : %d fin routine\n", philo->rank);


	

// 	printf("Philosophe : %d debut routine\n", (*philo).rank);

// 	usleep(500000);

// 	printf("Philosophe : %d fin routine\n", (*philo).rank);



	
// 	printf("Philosophe : %lu debut routine\n", philo[i].thread);

// 	usleep(500000);

// 	printf("Philosophe : %lu fin routine\n", philo[i].thread);


	
// 	// i++;
// 	return (NULL);
// }



// void	init_thread(t_data *data)
// {

// 	int i;

// 	i = 0;

// 	while (i < data->philos->nb_philos)
// 	{
// 		if (pthread_create(&data->philos[i].thread, NULL, &routine, &data->philos[i]) != 0)
// 		{
// 			printf("that's fuckep up son");
// 			exit(EXIT_FAILURE);
// 		}
// 		sleep (2);
// 		printf("\n\n%d\n\n", i);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < data->philos[0].nb_philos)
// 	{
// 		pthread_join(data->philos[i].thread, NULL);
// 		i++;
// 	}
// }

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;

	ft_verif_argc(argc);
	ft_verif_argv(argv);
	
	data = ft_init(argv, data);
	if (!data)
		return (1);
	init_thread(data);

	if (data->philos)
		free (data->philos);
	if (data)
		free (data);

	printf("\n\n\nENDING\n\n\n");
	return (0);
}



