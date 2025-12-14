/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 21:34:55 by brfialho          #+#    #+#             */
/*   Updated: 2025/12/13 22:04:22 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_table	*init_mutex(t_table *table);
static void		assign_philos_fork(t_table *table);

t_table	*init_table(int argc, char **argv)
{
	t_table	*table;
	long	input[5];
	int		i;

	if (!validate_input(input, argc, ++argv))
		return (printf(INPUT), NULL);
	table = ft_calloc(1, sizeof(t_table) + sizeof(t_philo) * input[PHILO]);
	if (!table)
		return (printf(MALLOC), NULL);
	i = -1;
	while (++i < 5)
		table->input[i] = input[i];
	if (!init_mutex(table))
		return (printf("%s", MUTEX), NULL);
	gettimeofday(&table->start, NULL);
	return (table);
}

void	init_threads(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->input[PHILO])
		pthread_create(&table->philo[i].thread, NULL, routine, \
&table->philo[i]);
}

static t_table	*init_mutex(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->input[PHILO])
	{
		if (pthread_mutex_init(&table->philo[i].fork, NULL))
			return (free_all(table, i, FALSE, FALSE), NULL);
		table->philo[i].id = i + 1;
		table->philo[i].table = table;
	}
	if (pthread_mutex_init(&table->print, NULL))
		return (free_all(table, i, FALSE, FALSE), NULL);
	if (pthread_mutex_init(&table->monitor, NULL))
		return (free_all(table, i, TRUE, FALSE), NULL);
	assign_philos_fork(table);
	return (table);
}

static void	assign_philos_fork(t_table *table)
{
	int	i;
	int	philo;

	philo = table->input[PHILO];
	i = -1;
	while (++i < philo)
	{
		table->philo[i].first = &table->philo[i].fork;
		table->philo[i].second = &table->philo[(i + 1) % philo].fork;
	}
	table->philo[philo - 1].first = &table->philo[0].fork;
	table->philo[philo - 1].second = &table->philo[philo - 1].fork;
}
