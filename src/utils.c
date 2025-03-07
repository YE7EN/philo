/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:53:58 by quentin           #+#    #+#             */
/*   Updated: 2025/03/07 13:25:20 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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