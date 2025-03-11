/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:53:58 by quentin           #+#    #+#             */
/*   Updated: 2025/03/11 15:07:11 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

time_t	get_current_time(void)
{
	struct timeval	time;
	time_t current_time;
	
	if (gettimeofday(&time, NULL) == -1)
		write(2, "error in gettimeofday process\n", 31);
	current_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (current_time);
}

int	ft_atoi(const char *nptr)
{
	int	res;
	
	res = 0;
	while (*nptr)
	{
		if (*nptr < '0' || *nptr > '9')
		{
			printf("Error\nBad args detected\n");	
			return (-1);
		} 
		res = res * 10 + (*nptr - '0');
		nptr++;
	}
	return (res);
}