/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 06:26:27 by brfialho          #+#    #+#             */
/*   Updated: 2025/12/14 11:02:56 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main()
{
	sem_unlink("philo_print");
	sem_unlink("philo_fork");
	sem_unlink("philo_nuke");
	sem_unlink("philo_monitor");
	sem_unlink("philo_full");
	sem_unlink("philo_every_full");
	sem_unlink("philo_big_nuke");
}