/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 21:18:59 by brfialho          #+#    #+#             */
/*   Updated: 2025/12/13 21:45:53 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_time(t_table *table)
{
	struct timeval	now;
	unsigned long	delta_time;

	gettimeofday(&now, NULL);
	delta_time = (now.tv_sec - table->start.tv_sec) * 1000000 \
					+ now.tv_usec - table->start.tv_usec;
	return (delta_time / 1000);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*array;

	if (size && nmemb > ((size_t) -1) / size)
		return (NULL);
	array = malloc(nmemb * size);
	if (!array)
		return (NULL);
	memset(array, 0, nmemb * size);
	return (array);
}

void	philo_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print);
	printf(FARM, get_time(philo->table), philo->id);
	pthread_mutex_unlock(&philo->table->print);
}

void	print_philo(t_philo *philo, char *s)
{
	if (is_end(philo->table))
		return ;
	pthread_mutex_lock(&philo->table->print);
	printf(PRINT, get_time(philo->table), philo->id, s);
	pthread_mutex_unlock(&philo->table->print);
}

char	is_end(t_table *table)
{
	pthread_mutex_lock(&table->monitor);
	if (table->end)
		return (pthread_mutex_unlock(&table->monitor), TRUE);
	return (pthread_mutex_unlock(&table->monitor), FALSE);
}

