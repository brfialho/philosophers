/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 00:04:37 by brfialho          #+#    #+#             */
/*   Updated: 2025/12/14 00:10:49 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


int main()
{
	int philos = 5;
	pid_t pid = 1;
	while (philos--)
		if (pid)
			pid = fork();

	pid ? printf("PARENT\n") : printf("CHILD\n");
}