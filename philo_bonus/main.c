/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:43:06 by brfialho          #+#    #+#             */
/*   Updated: 2025/12/14 03:43:20 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	kill_zombies(int pid);


int	init_childs(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->input[PHILO])
	{
		if (table->is_main)
			table->pid[i] = fork();
		// if (table->pid[i] < 0)
		// 	return (kill_zombies(--i), FALSE);
		if (!table->pid[i])
		{
			table->is_main = FALSE;
			break;
		}
	}
	table->philo.id = ++i;
	return (TRUE);
}

void	kill_zombies(int n_pid)
{
	int	i;

	i = -1;
	while (++i < n_pid)
		waitpid(0, NULL, 0);
}

void	routine(t_table *table)
{
	// while (TRUE)
	// {
	// 	printf(PRINT, get_time(table), philo.pid, THINKING);
	// 	usleep(1000);
	// 	// philo_eat(philo);
	// 	printf(PRINT, get_time(table), philo.pid, SLEEPING);
	// 	usleep(table->input[SLEEP] * 1000);
	// }
	printf("%d\n", table->philo.id);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	table = init_table(argc, argv);
	if (!table)
		return (ERROR);
	init_childs(table);
	if (table->is_main == FALSE)
	 	routine(table);
	//monitor(table);
	for (int i = 0; i < table->input[PHILO]; i++)
	table->is_main ? printf("pid[%d]: %d\n", i, table->pid[i]) : 0;
	kill_zombies(table->input[PHILO]);
	free_all(table);
}
