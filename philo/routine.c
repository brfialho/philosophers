/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 21:46:11 by brfialho          #+#    #+#             */
/*   Updated: 2025/12/13 21:47:37 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_eat(t_philo *philo);
static char	get_fork(t_philo *philo);

void	*routine(void *philo)
{
	t_philo *p;

	p = (t_philo *)philo;
	if (p->id % 2)
		usleep(1000);
	while (!is_end(p->table))
	{
		print_philo(philo, THINKING);
		usleep(1000);
		philo_eat(philo);
		if (is_end(p->table))
			return (p);
		print_philo(p, SLEEPING);
		usleep(p->table->input[SLEEP] * 1000);
		if (is_end(p->table))
			return (p);
	}
	return (p);
}

static void	philo_eat(t_philo *philo)
{
	if (get_fork(philo) == FALSE)
		return ;
	pthread_mutex_lock(&philo->table->monitor);
	philo->eaten++;
	philo->last_meal = get_time(philo->table);
	pthread_mutex_unlock(&philo->table->monitor);
	print_philo(philo, EATING);
	usleep(philo->table->input[EAT] * 1000);
	pthread_mutex_unlock(philo->first);
	pthread_mutex_unlock(philo->second);
}

static char	get_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->first);
	print_philo(philo, FORK);
	if (philo->table->input[PHILO] == 1)
		usleep(philo->table->input[STARVE] * 1000);
	if (is_end(philo->table))
		return (pthread_mutex_unlock(philo->first), FALSE);
	pthread_mutex_lock(philo->second);
	print_philo(philo, FORK);
	return (TRUE);
}
