/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:26:35 by pjurdana          #+#    #+#             */
/*   Updated: 2025/03/12 18:17:40 by quentin          ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo philos[ft_atoi(argv[1])];
	pthread_mutex_t	forks[ft_atoi(argv[1])];

	ft_verif_argc(argc);
	init_data(&data, philos);
	init_fork(forks, ft_atoi(argv[1]));
	if (init_philos(argv, &data, philos, forks) != 0)
		return (1);
	printf("\n\nrank after init : %d\n\n", philos[4].rank);
	
	//jusqu'ici on est clean//
	launch_thread(&data);

	printf("\n\nENDING\n\n");
	return (0);
}



