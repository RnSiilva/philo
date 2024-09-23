/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrong_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 02:20:34 by resilva           #+#    #+#             */
/*   Updated: 2024/09/20 03:53:38 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/**
 * @brief Neste exercicio vemos o caso da criacao de N threads dentro de um 
 * loop, e no mesmo loop a funcao JOIN (que eh responsavel por esperar a thread
 * especificada terminar). O problema eh que iniciar e esperar no mesmo loop, 
 * acarreta no problema de que as threads nao serao executas paralelamente, e 
 * sim uma de cada vez. Entao devemos fazer a inicializacao em um loop, e a espera 
 * (JOIN) em outro loop.
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
		if(pthread_create(th + i, NULL, &routine, NULL)) {
			perror("Failed to create thread!");
			return (1);
		}
		printf("Thread %d has started\n", i);
		if (pthread_join(th[i], NULL)) {
			perror("Failed to join thread!");
			return (2);
		}
		printf("Thread %d has finished execution\n", i);
	}
	printf("Number of mails: %d\n", mails);
	pthread_mutex_destroy(&mutex);
	return (0);
}
