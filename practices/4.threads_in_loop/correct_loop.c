/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 03:14:09 by resilva           #+#    #+#             */
/*   Updated: 2024/09/20 03:53:32 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/**
 * @brief Inicializacao das threads em um loop, e JOIN em outro, dessa forma 
 * temos o uso da funcao routine de forma paralela.
 */

int	mails = 0;
pthread_mutex_t	mutex;

void	*routine()
{
	for (int i = 0; i < 1000000; i++) {
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
}

int	main(void)
{
	pthread_t	th[4];

	int	i;

	for (i = 0; i < 4; i++) {
		if(pthread_create(th + i, NULL, &routine, NULL) != 0) {
			perror("Failed to create thread!");
			return (1);
		}
		printf("Thread %d has started\n", i);
	}
	for (i = 0; i < 4; i++) {
		if (pthread_join(th[i], NULL) != 0) {
			perror("Failed to join thread!");
			return (2);
		}
		printf("Thread %d has finished execution\n", i);
	}
	printf("Number of mails: %d\n", mails);
	pthread_mutex_destroy(&mutex);
	return (0);
}