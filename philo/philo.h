/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:43:48 by brfialho          #+#    #+#             */
/*   Updated: 2025/12/04 14:59:23 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

# ifndef ERROR
#  define ERROR -1
# endif

# ifndef PHILO
#  define PHILO 0
# endif

# ifndef STARVE
#  define STARVE 1
# endif

# ifndef EAT
#  define EAT 3
# endif

# ifndef SLEEP
#  define SLEEP 4
# endif

# ifndef FULL
#  define FULL 5
# endif

# ifndef INT_MAX
#  define INT_MAX 2147483647
# endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

#endif