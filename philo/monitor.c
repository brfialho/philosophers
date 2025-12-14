/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 21:30:23 by brfialho          #+#    #+#             */
/*   Updated: 2025/12/13 22:14:12 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	monitor_helper(t_table *table);

void	monitor(t_table *table)
{
	int	loop;

	loop = TRUE;
	while (loop)
	{
		pthread_mutex_lock(&table->monitor);
		if (!monitor_helper(table))
		{
			loop = FALSE;
			table->end = TRUE;
		}
		pthread_mutex_unlock(&table->monitor);
		usleep(1 * 100);
	}
}

static char	monitor_helper(t_table *table)
{
	int	i;
	int	full_eaten;

	i = -1;
	full_eaten = 0;
	while (++i < table->input[PHILO])
	{
		if (get_time(table) - table->philo[i].last_meal > \
(unsigned long)table->input[STARVE])
			return (philo_die(&table->philo[i]), FALSE);
		if (table->input[FULL] != -1
			&& table->philo[i].eaten >= table->input[FULL])
			full_eaten++;
	}
	if (full_eaten == table->input[PHILO])
	{
		pthread_mutex_lock(&table->print);
		printf(HA PPY, get_time(table));
		pthread_mutex_unlock(&table->print);
		return (FALSE);
	}
	return (TRUE);
}
