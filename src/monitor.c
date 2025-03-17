/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:25:31 by quentin           #+#    #+#             */
/*   Updated: 2025/03/13 17:16:57 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"









void	philo_scribing(char *str, t_philo *philo, int rank)
{
	time_t time;

	// besoin d'empecher les philo d'ecrire si l'un d'eux est mort


	pthread_mutex_lock(philo->write_lock);

	time = get_current_time() - philo->start_time;

	// printf("%ld %d %s", time, rank, str);

	// rank++;
// halloha cousin
// comment vous vous en sortez? biengggg plus ou moinsse 

// et toi ?
// ca va j ai la flemme de bosser mais bon, j'aide louise un peu et tout et tout et j'ai commence les CPP pcq tim n'est plus la, de plus, 
//la vie ici est assez contraignante, pas mal de bruits et d'odeurs. de la gueule notamment me dit louise, puis euh, jsais pas, 
//vous trouvez pas que c une fraude antoine sans lunettes ?
// oui faites gaffe mdr
// moi aussi je le deteste en vrai mais il est a cote ! quelqun a parle de pizza du coup il est plus trop la mais on sait jamaisC BON IL EST PARTI GO TRASHTALK
// #le palais dedobberman originel xD
//pourquoi ? par ce qu'il est a cotes de toi que tu demandes ? mdrrrrrrrrrrrrr trop drole
// src???



//il fait que pleurer mais je le console 
	printf("\n%ld | %d | %s\n", time, rank, str);

	if (*philo->dead == 0)
		pthread_mutex_unlock(philo->write_lock);


}

int	check_if_all_eaten(void *arg)
{
	t_philo	*philo;
	int		i;
	int		for_all;
	
	i = 0;
	philo = (t_philo *) arg;
	for_all = 0;
	while (i < philo->nb_philos)
	{
		if (philo[i].meals_eaten >= philo->num_times_to_eat && philo->num_times_to_eat > 0)
		{
				for_all++;
		}
			if (for_all == philo->nb_philos)
				return (1);
			i++;
	}
	return (0);
}
int	check_death(void *arg)
{
	t_philo	*philo;
	time_t	time;
	int	i;

	i = 0;
	philo = (t_philo *)arg;

	while (1)
	{
		i = 0;

		while (i < philo->nb_philos)
		{
			time = get_current_time();
			
			pthread_mutex_lock(philo[i].meal_lock);
			
			if (time - philo[i].last_meal >= philo[i].time_to_die)
			{
				pthread_mutex_lock(philo[i].dead_lock);
				
				//printf("\n\n\nHALLO JE SUIS MORT OU PAS ???\n\n\n");
				(*philo[i].dead = 1);
				philo_scribing("mort 🪦​", philo, philo[i].rank);
				pthread_mutex_unlock(philo[i].dead_lock);
				break ;
			}
				
				pthread_mutex_unlock(philo[i].meal_lock);
				
				usleep(5);
				i++;
			}
			if (check_if_all_eaten(philo) == 1)
			{
				//printf ("\n\n\n\nedrtfyguhijn\n\n\n");
			
			
				return (1);
			
			
			}
			if (*philo->dead == 1)
			exit(EXIT_FAILURE);
	}
	return (0);
}	


void	*supervisor(void *arg)
{
	t_philo *philos;

	philos = (t_philo *) arg;
	while (1)
	{
		if (check_death(philos) == 1) // || check_if_all_eaten(philos) == 1)
		{
			//printf("j'ai bien mange woulah\n\n\n");
			exit(EXIT_SUCCESS);
			break;
		}
	
	}
	return (arg);
}