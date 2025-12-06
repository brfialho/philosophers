/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:43:06 by brfialho          #+#    #+#             */
/*   Updated: 2025/12/06 18:18:03 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	philo_atol(char *s)
{
	long	sum;
	
	sum = 0;
	while (*s)
	{
		if (!(*s >= '0' && *s <= '9'))
			return (ERROR);
		sum = sum * 10 + *s++ - '0';
		if (sum > 2147483647)
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

void	free_all(t_table *table, int m_count)
{
	int	i;

	i = -1;
	while (++i < m_count)
		pthread_mutex_destroy(&table->philo[i].fork);
	free(table);
}

t_table	*init_table(int argc, char **argv)
{
	t_table	*table;
	long	input[5];
	int		i;

	if (!validate_input(input, argc, ++argv))
		return (printf("Invalid Input.\n"), NULL);
	table = ft_calloc(1, sizeof(t_table) + sizeof(t_philo) * input[PHILO]);
	if (!table)
		return (printf("Malloc Error.\n"), NULL);
	i = -1;
	while (++i < 5)
		table->input[i] = input[i];
	i = -1;
	while (++i < input[PHILO])
	{
		if (pthread_mutex_init(&table->philo[i].fork, NULL))
			free_all(table, i);
		table->philo[i].id = i;
		table->philo[i].table = table;
	}
	return (table);
}

void	*routine(void *philo)
{
	printf("CRIOU O %d\n", ((t_philo *)philo)->id);
	return (philo);
}

void	init_threads(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->input[PHILO])
	{
		pthread_create(&table->philo[i].thread, NULL, routine, &table->philo[i]);
		pthread_detach(table->philo[i].thread);
	}
}


int main(int argc, char **argv)
{
	t_table *table;

	table = init_table(argc, argv);
	if (!table)
		return (ERROR);

	// for (int i = 0; i < 5; i++)
	// 	printf("%ld\n", table->input[i]);
	// printf("Só sei que nada sei\n");

	init_threads(table);

	sleep(3);

	free_all(table, table->input[PHILO]);
}
