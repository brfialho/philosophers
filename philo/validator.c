/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 21:32:47 by brfialho          #+#    #+#             */
/*   Updated: 2025/12/13 21:59:43 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	philo_atol(char *s);

int	validate_input(long *data, int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (FALSE);
	i = -1;
	while (++i < argc - 1)
	{
		data[i] = philo_atol(argv[i]);
		if (data[i] == ERROR
			|| (i < 4 && data[i] == 0))
			return (FALSE);
	}
	if (argc == 5)
		data[FULL] = -1;
	return (TRUE);
}

static long	philo_atol(char *s)
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
