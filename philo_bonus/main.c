/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:43:06 by brfialho          #+#    #+#             */
/*   Updated: 2025/12/14 07:39:01 by brfialho         ###   ########.fr       */
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

void	philo_die(t_table *table)
{
	sem_wait(table->print);
	printf(FA RM, get_time(table), table->philo.id);
	sem_post(table->nuke);
}

static void	monitor_helper(t_table *table)
{
	int	i;
	int	full_eaten;

	i = -1;
	full_eaten = 0;
	while (++i < table->input[PHILO])
	{
		if (get_time(table) - table->philo.last_meal > \
(unsigned long)table->input[STARVE])
			philo_die(table);
		// if (table->input[FULL] != -1
		// 	&& table->philo.eaten >= table->input[FULL])
		// 	full_eaten++;
	}
	// if (full_eaten == table->input[PHILO])
	// {
	// 	pthread_mutex_lock(&table->print);
	// 	printf(HA PPY, get_time(table));
	// 	pthread_mutex_unlock(&table->print);
	// 	return (FALSE);
	// }
	return ;
}

void	*monitor(void *table)
{
	t_table *t;

	t = table;
	while (TRUE)
	{
		sem_wait(t->monitor);
		monitor_helper(t);
		sem_post(t->monitor);
		usleep(1000);
	}
	return (table);
}

static void	philo_eat(t_table *table)
{
	sem_wait(table->fork);
	sem_wait(table->fork);
	
	sem_wait(table->monitor);
	table->philo.eaten++;
	table->philo.last_meal = get_time(table);
	sem_post(table->monitor);

	print_philo(table, EATING);
	usleep(table->input[EAT] * 1000);
	
	sem_post(table->fork);
	sem_post(table->fork);
}

void	routine(t_table *table)
{
	if (table->philo.id % 2)
		usleep(1000);
	pthread_create(&table->philo.thread, NULL, monitor, table);
	pthread_detach(table->philo.thread);
	while (TRUE)
	{
		print_philo(table, THINKING);
		usleep(1000);
		
		philo_eat(table);
		
		print_philo(table, SLEEPING);
		usleep(table->input[SLEEP] * 1000);
	}
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

void	kill_childs(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->input[PHILO])
		kill(table->pid[i], SIGTERM);
}

void	destroy_sem(void)
{
	sem_unlink("/philo_nuke");
	sem_unlink("/philo_fork");
	sem_unlink("/philo_monitor");
	sem_unlink("/philo_print");
}

int	main(int argc, char **argv)
{
	t_table	*table;

	table = init_table(argc, argv);
	if (!table)
		return (ERROR);
	init_childs(table);
	sem_wait(table->nuke);
	sem_wait(table->nuke);
	kill_childs(table);
	kill_zombies(table->input[PHILO]);
	destroy_sem();
	free_all(table);
}
