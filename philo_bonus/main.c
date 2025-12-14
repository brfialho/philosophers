/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:43:06 by brfialho          #+#    #+#             */
/*   Updated: 2025/12/14 11:17:05 by brfialho         ###   ########.fr       */
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

void	philo_die(t_table *table)
{
	int i;

	sem_wait(table->print);
	printf(FA RM, get_time(table), table->philo.id);
	i = -1;
	sem_post(table->nuke);
}

static void	monitor_helper(t_table *table)
{
	int	i;

	i = -1;
	if (get_time(table) - table->philo.last_meal > \
(unsigned long)table->input[STARVE])
		philo_die(table);
	if (table->input[FULL] != -1
		&& table->philo.eaten == table->input[FULL]
		&& table->philo.is_full == FALSE)
	{
		table->philo.is_full = TRUE;
		sem_post(table->full);
	}
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
	print_philo(table, FORK);
	sem_wait(table->fork);
	print_philo(table, FORK);
	
	sem_wait(table->monitor);
	table->philo.eaten++;
	table->philo.last_meal = get_time(table);
	sem_post(table->monitor);

	print_philo(table, EATING);
	usleep(table->input[EAT] * 1000);
	
	sem_post(table->fork);
	sem_post(table->fork);
}
void	*monitor_full(void *table)
{
	t_table *t;

	t = table;
	sem_wait(t->everyone_full);
	free(table);
	exit(0);
	return (table);
}

void	*monitor_death(void *table)
{
	t_table	*t;

	t = table;
	sem_wait(t->big_nuke);
	free(table);
	exit(1);
	return (table);
}

void	routine(t_table *table)
{
	if (table->philo.id % 2)
		usleep(1000);
	pthread_create(&table->philo.monitor, NULL, monitor, table);
	pthread_create(&table->philo.wait_death, NULL, monitor_death, table);
	pthread_create(&table->philo.wait_full, NULL, monitor_full, table);
	pthread_detach(table->philo.monitor);
	pthread_detach(table->philo.wait_death);
	pthread_detach(table->philo.wait_full);
	while (TRUE)
	{
		print_philo(table, THINKING);
		usleep(1000);
		
		philo_eat(table);
		
		print_philo(table, SLEEPING);
		usleep(table->input[SLEEP] * 1000);
	}
}

void	kill_childs(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->input[PHILO])
		waitpid(table->pid[i], NULL, 0);
}

void	destroy_sem(void)
{
	sem_unlink("/philo_nuke");
	sem_unlink("/philo_fork");
	sem_unlink("/philo_monitor");
	sem_unlink("/philo_print");
	sem_unlink("/philo_full");
}

void	*wait_for_full(void *table)
{
	t_table *t;
	int		i;

	t = table;
	i = -1;
	while (++i < t->input[PHILO])
		sem_wait(t->full);
	sem_wait(t->print);
	i = -1;
	while (++i < t->input[PHILO])
		sem_post(t->everyone_full);
	printf(HA PPY, get_time(table));
	return (0);
}

void	*wait_for_death(void *table)
{
	t_table *t;
	int		i;

	t = table;
	i = -1;
	sem_wait(t->nuke);
	i = -1;
	while (++i < t->input[PHILO])
		sem_post(t->big_nuke);
	return (0);
}


void	init_evil_twins(t_table *table)
{
	pthread_create(&table->twin_full, NULL, wait_for_full, table);
	pthread_create(&table->twin_death, NULL, wait_for_death, table);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	table = init_table(argc, argv);
	if (!table)
		return (ERROR);
	init_childs(table);
	init_evil_twins(table);
	kill_childs(table);
	destroy_sem();
	free_all(table);
}
