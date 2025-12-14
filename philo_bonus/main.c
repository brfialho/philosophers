/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:43:06 by brfialho          #+#    #+#             */
/*   Updated: 2025/12/14 17:13:34 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine(t_table *table);

char	is_end(t_table *table)
{
	sem_wait(table->monitor);
	if (table->is_end)
		return(sem_post(table->monitor), TRUE);
	return (sem_post(table->monitor), FALSE);
}

void	close_sem(t_table *table)
{
	sem_close(table->die);
	sem_close(table->fork);
	sem_close(table->print);
	sem_close(table->monitor);
	sem_close(table->full);
}

void	unlink_sem(void)
{
	sem_unlink("/philo_die");
	sem_unlink("/philo_fork");
	sem_unlink("/philo_monitor");
	sem_unlink("/philo_print");
	sem_unlink("/philo_full");
}

void	set_end(t_table *table)
{
	sem_wait(table->monitor);
	table->is_end = TRUE;
	sem_post(table->monitor);
}

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
	if (table->is_end)
		return ;
	sem_post(table->die);
	sem_wait(table->print);
	printf(FA RM, get_time(table), table->philo.id);
	sem_post(table->print);
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
		if (t->is_end)
			return (sem_post(t->monitor), table);
		sem_post(t->monitor);
		usleep(1000);
	}
	return (table);
}

static void	*philo_eat(t_table *table)
{
	sem_wait(table->fork);
	print_philo(table, FORK);
	if (is_end(table))
		return (sem_post(table->fork), NULL);
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
	return (NULL);
}


void	*monitor_death(void *table)
{
	t_table *t;

	t = table;
	sem_wait(t->die);
	set_end(table);
	sem_post(t->die);
	return (0);
}

void	routine(t_table *table)
{
	if (table->philo.id % 2)
		usleep(1000);
	pthread_create(&table->philo.monitor, NULL, monitor, table);
	pthread_create(&table->philo.wait_death, NULL, monitor_death, table);
	while (TRUE)
	{
		print_philo(table, THINKING);
		usleep(1000);
		if (is_end(table))
			break;
		philo_eat(table);
		if (is_end(table))
			break;
		print_philo(table, SLEEPING);
		usleep(table->input[SLEEP] * 1000);
		if (is_end(table))
			break;
	}
	pthread_join(table->philo.monitor, NULL);
	pthread_join(table->philo.wait_death, NULL);
	close_sem(table);
	free(table);
	exit(0);
}

void	wait_childs(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->input[PHILO])
		waitpid(table->pid[i], NULL, 0);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	unlink_sem();
	table = init_table(argc, argv);
	if (!table)
		return (ERROR);
	init_childs(table);
	// pthread_create(&table->twin_full, NULL, wait_for_full, table);
	// pthread_create(&table->twin_death, NULL, wait_for_death, table);
	wait_childs(table);
	close_sem(table);
	unlink_sem();
	free(table);
}
