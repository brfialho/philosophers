/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:02:21 by brfialho          #+#    #+#             */
/*   Updated: 2025/12/04 14:50:36 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>


void* foo(void* arg)
{
    static int i = 0;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    pthread_mutex_lock(&mutex);
    printf("Created a new thread: %d\n", i++);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main()
{
    
    // Create a pthread_t variable to store
    // thread ID
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;
    pthread_t thread4;
    
    // Creating a new thread. 
    pthread_create(&thread1, NULL, foo, NULL);
    pthread_create(&thread2, NULL, foo, NULL);
    pthread_create(&thread3, NULL, foo, NULL);
    pthread_create(&thread4, NULL, foo, NULL);

    sleep(1);
    
    return 0;
}