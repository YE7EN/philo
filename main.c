/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:26:35 by pjurdana          #+#    #+#             */
/*   Updated: 2025/03/06 12:03:57 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

t_philo	*ft_init(char **argv, t_philo **philo)
{

	*philo = NULL;
	*philo = malloc(sizeof(t_philo));
	if (!(*philo))
		return (NULL);
		
	(*philo)->nb_philos = (ft_atoi(argv[1]));
	(*philo)->time_to_die = (ft_atoi(argv[2]));
	(*philo)->time_to_eat = (ft_atoi(argv[3]));
	(*philo)->time_to_sleep = (ft_atoi(argv[4]));
	if (argv[5])
		(*philo)->meals_eaten = (ft_atoi(argv[5]));


	// printf("%d\n", (*philo)->nb_philos);
	// printf("%zu\n", (*philo)->time_to_die);
	// printf("%zu\n", (*philo)->time_to_eat);
	// printf("%zu\n", (*philo)->time_to_sleep);
	// if (argv[5])
	// 	printf("%d\n", (*philo)->meals_eaten);

	// printf("\n\n\n");
	return (*philo);



}

int primes[10] = {1, 4, 7, 8, 6, 21};

void*	routine()
{


	printf("hallo\n\n\n");

	// int index = *(int*)i;
	
	// printf("%d\n", primes[index]);

	
	// t_philo	*philo;
	
	// philo = (t_philo *)p;
	// while (1)
	// {
		// int i = 0;
		// i++;
		// printf("%d", i);
		// break ;
	// }
	// return (p);
	// free (i);
	return (0);
}

int	init_thread(t_philo	*philo)
{
	// t_data		*th;
	int			i;

	i = 0;
	
	while (i < philo->nb_philos)
	{
		int *a = malloc(sizeof(int));
		*a = i;
		// printf("hallo\n\n\n");
		if (pthread_create(&philo->thread[i], NULL, &routine, NULL) != 0)
			perror("error");
		// printf("ui\n\n\n");
		
		i++;
	}

	
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*philo;

	
	ft_verif_argc(argc);
	ft_verif_argv(argv);

	ft_init(argv, &philo);

	
	// printf("%d\n", philo->nb_philos);
	// printf("%zu\n", philo->time_to_die);
	// printf("%zu\n", philo->time_to_eat);
	// printf("%zu\n", philo->time_to_sleep);
	// if (argv[5])
	// 	printf("%d\n", philo->meals_eaten);
	
	init_thread(philo);

	printf("\n\n\nGG\n\n\n");
	return (0);
}



