/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 02:12:47 by resilva           #+#    #+#             */
/*   Updated: 2024/09/20 02:26:23 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/**
 * @brief Neste exercicio resolveremos o caso de race condition apresentado no 
 * caso anterior (2.race_conditions), fazendo o bloqueio de trechos criticos 
 * do programa utilizando mutex.
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
	pthread_t	t1, t2, t3, t4;

	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return (2);
	if (pthread_create(&t3, NULL, &routine, NULL) != 0)
		return (3);
	if (pthread_create(&t4, NULL, &routine, NULL) != 0)
		return (4);
	if (pthread_join(t1, NULL) != 0)
		return (5);
	if (pthread_join(t2, NULL) != 0)
		return (6);	
	if (pthread_join(t3, NULL) != 0)
		return (6);
	if (pthread_join(t4, NULL) != 0)
		return (6);
	printf("Number of mails: %d\n", mails);
	pthread_mutex_destroy(&mutex);
	return (0);
}