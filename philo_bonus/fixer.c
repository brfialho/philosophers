/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 06:26:27 by brfialho          #+#    #+#             */
/*   Updated: 2025/12/14 06:29:08 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main()
{
	sem_unlink("fork");
	sem_unlink("nuke");
	sem_unlink("monitor");
	sem_unlink("philo_print");
	sem_unlink("monitor_");
	sem_unlink("philo_fork");
	sem_unlink("philo_nuke");
	sem_unlink("print");
	sem_unlink("philo_monitor");
}