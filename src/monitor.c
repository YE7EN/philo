









#include "../includes/philo.h"









void	philo_scribing(char *str, t_philo *philo, int rank)
{
	time_t time;

	pthread_mutex_lock(philo->write_lock);

	time - get_current_time() - philo->start_time;

	printf("%d %d %s", time, rank, str);

	pthread_mutex_unlock(philo->write_lock);


}