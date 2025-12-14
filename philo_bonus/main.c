/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:43:06 by brfialho          #+#    #+#             */
/*   Updated: 2025/12/14 03:10:35 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	kill_zombies(int n_pid);


int	init_childs(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->input[PHILO])
	{
		if (table->pid[i])
			table->pid[i + 1] = fork();
		if (table->pid[i + 1] < 0)
			return (kill_zombies(i), FALSE);
	}
	table->philo.id = i;
	return (TRUE);
}

int	kill_zombies(int n_pid)
{
	int	i;

	i = -1;
	while (++i < n_pid)
		waitpid(0, NULL, 0);
	return (TRUE);
}

// void	routine(t_table *table)
// {
// 	t_philo	philo;

// 	memset(&philo, 0, sizeof(t_philo));
// 	philo.pid = table->pid;
// 	while (TRUE)
// 	{
// 		printf(PRINT, get_time(table), philo.pid, THINKING);
// 		usleep(1000);
// 		// philo_eat(philo);
// 		printf(PRINT, get_time(table), philo.pid, SLEEPING);
// 		usleep(table->input[SLEEP] * 1000);
// 	}
// 	exit(0);
// }

int	main(int argc, char **argv)
{
	t_table	*table;

	table = init_table(argc, argv);
	if (!table)
		return (ERROR);
	init_childs(table);
	// if (table->pid == 0)
	// 	routine(table);
	//monitor(table);
	// kill_zombies(table->input[PHILO]);
	// for (int i = 0; i < 6; i++)
	// 	table->pid[i] ? printf("id %d pid[%d]: %d\n", table->philo.id, i, table->pid[i]) : 0;
	printf("%d\n", table->is_main);
	// free_all(table);
}
