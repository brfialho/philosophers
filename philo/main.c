/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:43:06 by brfialho          #+#    #+#             */
/*   Updated: 2025/12/11 22:14:49 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(t_table *table)
{
	struct timeval	now;
	long			delta_time;

	gettimeofday(&now, NULL);
	delta_time = (now.tv_sec - table->start.tv_sec) * 1000000 \
					+ now.tv_usec - table->start.tv_usec;
	return (delta_time / 1000);
}

long	philo_atol(char *s)
{
	long	sum;
	
	sum = 0;
	while (*s)
	{
		if (!(*s >= '0' && *s <= '9'))
			return (ERROR);
		sum = sum * 10 + *s++ - '0';
		if (sum > INT_MAX)
			return (ERROR);
	}
	return (sum);
}

int	validate_input(long *data, int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (FALSE);
	i = -1;
	while (++i < argc - 1)
	{
		data[i] = philo_atol(argv[i]);
		if (data[i] == ERROR)
			return (FALSE);
	}
	if (argc == 5)
		data[FULL] = -1;
	return (TRUE);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*array;

	if (size && nmemb > ((size_t) -1) / size)
		return (NULL);
	array = malloc(nmemb * size);
	if (!array)
		return (NULL);
	memset(array, 0, nmemb * size);
	return (array);
}

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

void	assign_philos_fork(t_table *table)
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

t_table	*init_mutex(t_table *table)
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

char	is_end(t_table *table)
{
	pthread_mutex_lock(&table->monitor);
	if (table->end)
		return (pthread_mutex_unlock(&table->monitor), TRUE);
	return (pthread_mutex_unlock(&table->monitor), FALSE);
}

void	print_philo(t_philo *philo, char *s)
{
	if (is_end(philo->table))
		return ;
	pthread_mutex_lock(&philo->table->print);
	printf(PRINT, get_time(philo->table), philo->id, s);
	pthread_mutex_unlock(&philo->table->print);
}

void	philo_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->monitor);
	philo->is_dead = TRUE;
	pthread_mutex_unlock(&philo->table->monitor);
	pthread_mutex_lock(&philo->table->print);
	printf(FARM, get_time(philo->table), philo->id);
	pthread_mutex_unlock(&philo->table->print);
}

void	philo_sleep(t_philo *philo)
{
	print_philo(philo, SLEEPING);
	usleep(philo->table->input[SLEEP] * 1000);
}

char	get_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->first);
	print_philo(philo, FORK);
	if (is_end(philo->table))
		return (pthread_mutex_unlock(philo->first), FALSE);
	pthread_mutex_lock(philo->second);
	print_philo(philo, FORK);
	return (TRUE);
}
void	leave_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->first);
	pthread_mutex_unlock(philo->second);
}

void	philo_eat(t_philo *philo)
{
	print_philo(philo, THINKING);
	if (get_fork(philo) == FALSE)
		return ;
	print_philo(philo, EATING);
	usleep(philo->table->input[EAT] * 1000);
	leave_fork(philo);
	pthread_mutex_lock(&philo->table->monitor);
	philo->eaten++;
	pthread_mutex_unlock(&philo->table->monitor);
}

void	*routine(void *philo)
{
	t_philo *p = (t_philo *)philo;
	if (p->id % 2)
		usleep((p->table->input[EAT] * 1000) / p->table->input[PHILO]);
	while (!is_end(p->table))
	{
		philo_eat(philo);
		if (is_end(p->table))
			return (p);
		philo_sleep(philo);
		if (is_end(p->table))
			return (p);
	}
	return (p);
}

void	init_threads(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->input[PHILO])
		pthread_create(&table->philo[i].thread, NULL, routine, &table->philo[i]);
}

void	kill_threads(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->input[PHILO])
		pthread_join(table->philo[i].thread, NULL);
}
char	monitor_helper(t_table *table)
{
	int	i;
	int	full_eaten;

	i = -1;
	full_eaten = 0;
	while (++i < table->input[PHILO])
	{
		if (table->philo[i].is_dead)
			return (FALSE);
		if (table->input[FULL] != -1 
			&& table->philo[i].eaten >= table->input[FULL])
			full_eaten++;
	}
	if (full_eaten == table->input[PHILO])
		return (FALSE);
	return (TRUE);
}

void	monitor(t_table *table)
{
	int loop;

	loop = TRUE;
	while (loop)
	{
		pthread_mutex_lock(&table->monitor);
		if (!monitor_helper(table))
		{
			loop = FALSE;
			table->end = TRUE;
		}
		pthread_mutex_unlock(&table->monitor);
		usleep(1 * 1);
	}
}

int main(int argc, char **argv)
{
	t_table *table;

	table = init_table(argc, argv);
	if (!table)
		return (ERROR);
	init_threads(table);
	monitor(table);
	kill_threads(table);
	// for (int i = 0; i < table->input[PHILO]; i++)
	// 	if (table->philo[i].is_dead || table->philo[i].eaten >= 30)
	// 		printf("\n%d has eaten %d and died\n", table->philo[i].id, table->philo[i].eaten);
	free_all(table, table->input[PHILO], TRUE, TRUE);
}


// init all
// check every 10 ms for philo death
	// if dead change boolean
	// wait for threads to clean up

	
//if par go to eat
//while
//	think
//	eat
//  sleep
//