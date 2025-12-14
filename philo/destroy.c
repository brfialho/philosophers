/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 21:37:41 by brfialho          #+#    #+#             */
/*   Updated: 2025/12/13 21:38:19 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_table *table, int m_count, char print, char monitor)
{
	int	i;

	i = -1;
	while (++i < m_count)
		pthread_mutex_destroy(&table->philo[i].fork);
	if (print)
		pthread_mutex_destroy(&table->print);
	if (monitor)
		pthread_mutex_destroy(&table->monitor);
	free(table);
}

void	kill_threads(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->input[PHILO])
		pthread_join(table->philo[i].thread, NULL);
}

