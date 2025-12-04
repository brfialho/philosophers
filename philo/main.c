/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:43:06 by brfialho          #+#    #+#             */
/*   Updated: 2025/12/04 17:35:36 by brfialho         ###   ########.fr       */
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

// int	init_philos(t_table *table)
// {
// 	int	i;

// 	table->philo = ft_calloc(table->input[PHILO] + 1, sizeof(t_philo));
// 	if (!table->philo)
// 		return (FALSE);
// 	return (TRUE);
// }

int main(int argc, char **argv)
{
	t_table table;

	if (!validate_input(table.input, argc, ++argv))
		return (printf("Invalid Input\n"));
	for (int i = 0; i < 5; i++)
		printf("%ld\n", table.input[i]);
	// if (!init_philos(&table))
	// 	return (printf("Memory Error\n"));

	printf("Só sei que nada sei\n");
}
