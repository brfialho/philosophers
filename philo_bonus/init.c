/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 21:34:55 by brfialho          #+#    #+#             */
/*   Updated: 2025/12/14 04:39:37 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_sem(t_table *table);

t_table	*init_table(int argc, char **argv)
{
	t_table	*table;
	long	input[5];
	int		i;

	if (!validate_input(input, argc, ++argv))
		return (printf(INPUT), NULL);
	table = ft_calloc(1, sizeof(t_table) + sizeof(pid_t) * (input[PHILO]));
	if (!table)
		return (printf(MALLOC), NULL);
	i = -1;
	while (++i < 5)
		table->input[i] = input[i];
	table->is_main = TRUE;
	gettimeofday(&table->start, NULL);
	// init_sem(table);
	table->sem_prefix = SEM_NAME;
	return (table);
}

	// sem_open("/forks", O_CREAT, 0644, table->input[PHILO]);

