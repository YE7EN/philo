/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:26:35 by pjurdana          #+#    #+#             */
/*   Updated: 2025/03/07 13:25:35 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// static void	ft_verif_argv(char **argv)
// {
// 	int	i;

// 	i = 1;
// 	while (argv[i])
// 	{
// 		if (ft_atoi(argv[i]) == -1)
// 		{
// 			printf("ERROR\nWrong argument\n");
// 			exit (EXIT_FAILURE);
// 		}
// 		i++;
// 	}
// }

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
	t_data	*data;
	int		check_rt;

	check_rt = 0;
	data = NULL;

	ft_verif_argc(argc);
	//ft_verif_argv(argv);
	
	check_rt = init_value(argv, &data);
	if (check_rt != 0)
	{
		//gestion des erreurs et free en consequence
		return (1);
	}
	init_thread(data);

	if (data->philos)
		free (data->philos);
	if (data)
		free (data);

	printf("\n\n\nENDING\n\n\n");
	return (0);
}



