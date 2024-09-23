/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sum.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:04:57 by resilva           #+#    #+#             */
/*   Updated: 2024/09/20 17:20:46 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

/**
 * @brief Neste exemplo utlizamos 2 threads, um faz a soma da primeira metade de array de primos, e o segundo faz a soma da segunda metade de array primos. No main, fazemos a soma das duas metades.
 * 
 */

#define TH 2

int	primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

void	*routine(void *data)
{
	int	index = *(int *)data;
	int	sum = 0;
	
	for (int i = 0; i < 5; i++)
		sum += primes[index + i];
	printf("Local sum: %d\n", sum);
	*(int *)data = sum;
	return (data);
}

int	main(void)
{
	pthread_t	threads[TH];
	int			i;
	int			result;
	int			*ret;

	for (i = 0; i < TH; i++) {
		int	*a = malloc(sizeof(int));
		*a = i * 5;
		if (pthread_create(&threads[i], NULL, &routine, a)) {
			perror("Failed to create thread!");
			return (1);
		}
	}
	result = 0;
	for (i = 0; i < TH; i++) {
		if (pthread_join(threads[i], (void **)&ret)) {
			perror("Failed to create thread!");
			return (2);
		}
		result += *ret;
		free(ret);
	}
	printf("Result: %d\n", result);
}