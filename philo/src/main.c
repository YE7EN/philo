/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:26:35 by pjurdana          #+#    #+#             */
/*   Updated: 2025/03/19 14:57:10 by qumiraud         ###   ########.fr       */
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
	t_data			data;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int				nb_philos;

	nb_philos = ft_atoi(argv[1]);
	if (nb_philos < 1)
		return (1);
	philos = malloc(sizeof(t_philo) * nb_philos);
	forks = malloc(sizeof(pthread_mutex_t) * nb_philos);
	ft_verif_argc(argc);
	init_data(&data, philos);
	init_fork(forks, ft_atoi(argv[1]));
	if (init_philos(argv, &data, philos, forks) != 0)
	{
		free(philos);
		free(forks);
		return (1);
	}
	launch_thread(&data);
	free(philos);
	free(forks);
	return (0);
}
