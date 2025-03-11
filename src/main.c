/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:26:35 by pjurdana          #+#    #+#             */
/*   Updated: 2025/03/11 15:28:27 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	ft_verif_argc(int argc)
{
	if (argc != 5 && argc != 6)
	{
		printf("ERROR\nWrong number of argument\n");
		exit (EXIT_FAILURE);
	}
}

// void	init_fork(pthread_mutex_t *forks, int nb_philo)
// {
// 	int	i;

// 	i = 0;
// 	while (i < nb_philo)
// 	{
// 		pthread_mutex_init(&forks[i], NULL);
// 		i++;
// 	}
// }//to_init.c

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo *philos;
	pthread_mutex_t	*forks;
	// data = NULL;

	ft_verif_argc(argc);
	init_data(&data, &philos);
	init_fork(forks, data->philos->nb_philos);
	if (init_philos(argv, &data, forks) != 0)
		return (1);
	launch_thread(data);

	if (data->philos)
		free (data->philos);
	if (data)
		free (data);

	printf("\n\nENDING\n\n");
	return (0);
}



