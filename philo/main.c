/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:43:06 by brfialho          #+#    #+#             */
/*   Updated: 2025/12/02 12:45:13 by brfialho         ###   ########.fr       */
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
	}
	return (sum);
}

int	validate_input(long *data, int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (FALSE);
	i = 0;
	while (++i < argc)
	{
		data[i] = philo_atol(argv[i]);
		if (data[i] == ERROR)
			return (FALSE);
	}
	if (argc == 5)
		data[FULL] = -1;
	return (TRUE);
}

int main(int argc, char **argv)
{
	long	data[5];

	if (!validate_input(data, argc, argv))
		return (printf("Invalid Input\n"));

	printf("Só sei que nada sei\n");
}
