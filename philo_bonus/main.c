/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:43:06 by brfialho          #+#    #+#             */
/*   Updated: 2025/12/14 04:38:57 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	kill_zombies(int pid);
void	routine(t_table *table);


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
	if (table->is_main == FALSE)
		routine(table);
	return (TRUE);
}

void	kill_zombies(int n_pid)
{
	int	i;

	i = -1;
	while (++i < n_pid)
		waitpid(0, NULL, 0);
}

// void	monitor(t_table *table)
// {
// 	int	loop;

// 	loop = TRUE;
// 	while (loop)
// 	{
// 		if (table->philo.eaten)
// 	}
// }

void	init_monitor_sem(t_table *table)
{
	int	i;
	int	digits;
	int	n;

	i = -1;
	while (table->sem_prefix[++i])
		table->philo.sem_name[i] = table->sem_prefix[i];
	n = table->philo.id;
	digits = 1;
	while (n / 10)
	{
		n /= 10;
		digits++;
	}
	n = table->philo.id;
	while (digits--)
		table->philo.sem_name[i + digits] = n % 10 + '0';
	printf ("%s\n", table->philo.sem_name); 
}

void	routine(t_table *table)
{
	init_monitor_sem(table);
	// pthread_create(table->philo.thread, NULL, monitor, NULL);
	// pthread_detach(table->philo.thread);
	// while (TRUE)
	// {
	// 	printf(PRINT, get_time(table), table->philo.id, THINKING);
	// 	usleep(1000);
	// 	// philo_eat(philo);
	// 	printf(PRINT, get_time(table), table->philo.id, SLEEPING);
	// 	usleep(table->input[SLEEP] * 1000);
	// }
	exit(0);
}

// static char	monitor_helper(t_table *table)
// {
// 	int	i;
// 	int	full_eaten;

// 	i = -1;
// 	full_eaten = 0;
// 	while (++i < table->input[PHILO])
// 	{
// 		if (get_time(table) - table->philo[i].last_meal > \
// (unsigned long)table->input[STARVE])
// 			return (philo_die(&table->philo[i]), FALSE);
// 		if (table->input[FULL] != -1
// 			&& table->philo[i].eaten >= table->input[FULL])
// 			full_eaten++;
// 	}
// 	if (full_eaten == table->input[PHILO])
// 	{
// 		pthread_mutex_lock(&table->print);
// 		printf(HA PPY, get_time(table));
// 		pthread_mutex_unlock(&table->print);
// 		return (FALSE);
// 	}
// 	return (TRUE);
// }









int	main(int argc, char **argv)
{
	t_table	*table;

	table = init_table(argc, argv);
	if (!table)
		return (ERROR);
	init_childs(table);
	//monitor(table);
	kill_zombies(table->input[PHILO]);
	free_all(table);
}
