/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 21:34:55 by brfialho          #+#    #+#             */
/*   Updated: 2025/12/14 03:28:44 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	return (table);
}
