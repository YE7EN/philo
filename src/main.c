/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:26:35 by pjurdana          #+#    #+#             */
/*   Updated: 2025/03/10 11:46:57 by quentin          ###   ########.fr       */
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
	t_data	*data;

	data = NULL;

	ft_verif_argc(argc);
	
	if (init_value(argv, &data) != 0)
		return (1);
	init_thread(data);

	if (data->philos)
		free (data->philos);
	if (data)
		free (data);

	printf("\n\nENDING\n\n");
	return (0);
}



