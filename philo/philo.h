/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:43:48 by brfialho          #+#    #+#             */
/*   Updated: 2025/12/13 22:12:41 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

// Utils
# define INT_MAX 2147483647
# define TRUE 1
# define FALSE 0
# define ERROR -1

// Indexes for user input data array
# define PHILO 0
# define STARVE 1
# define EAT 2
# define SLEEP 3
# define FULL 4

// Print Messages
# define FORK "\033[38;5;255mhas taken a fork... \033[0m🍴\n"
# define EATING "\033[38;5;208mis eating... \033[0m🍔\n"
# define SLEEPING "\033[34mis sleeping... \033[0m💤\n"
# define THINKING "\033[1;37mis thinking... \033[0m💭\n"
# define FA "# \033[36m%ldms\033[0m | PHILO NUMBER: %d "
# define RM "\033[32mwent to the farm!\033[0m 🏡\n"
# define HA "# \033[36m%ldms\033[0m | "
# define PPY "\033[38;5;226mEvebody is full and happy!\033[0m 😊\n"
# define PRINT "# \033[36m%ldms\033[0m | PHILO NUMBER: %d %s\n"

// Error messages
# define INPUT "Invalid Input.\n"
# define MALLOC "Malloc Error.\n"
# define MUTEX "Mutex Init Error.\n"

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	fork;
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;
	unsigned long	last_meal;
	int				eaten;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	struct timeval	start;
	char			end;
	pthread_mutex_t	monitor;
	pthread_mutex_t	print;
	long			input[5];
	t_philo			philo[];
}	t_table;

// // Functions 
// Monitor
void			monitor(t_table *table);

// Validator
int				validate_input(long *data, int argc, char **argv);

// init
t_table			*init_table(int argc, char **argv);
void			init_threads(t_table *table);

// Destroy
void			free_all(t_table *table, int m_count, char print, char monitor);
void			kill_threads(t_table *table);

// Routine
void			*routine(void *philo);

// Utils
unsigned long	get_time(t_table *table);
void			*ft_calloc(size_t nmemb, size_t size);
void			philo_die(t_philo *philo);
void			print_philo(t_philo *philo, char *s);
char			is_end(t_table *table);

#endif
