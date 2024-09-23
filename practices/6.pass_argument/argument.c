/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 03:49:26 by resilva           #+#    #+#             */
/*   Updated: 2024/09/20 04:42:57 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

/**
 * @brief Neste exemplo vemos a passagem de argumentos para a funcao de rotina, que eh o quarto argumento da funcao pthread_create. Este argumento, assim como no exercicio 5, deve ser alocado, para que o valor nao seja somente local (no caso somente do main), mas possa ser acessado em outras funcoes.
 * 
 */

int	primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

void	*routine(void *data)
{
	int	index = *(int *)data;
	printf("%d ", primes[index]);
	free (data);
}

int	main(void)
{
	pthread_t	th[10];
	int			i;

	for (i = 0; i < 10; i++) {
		int	*a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&th[i], NULL, &routine, a)) {
			perror("Failed to create thread!");
			return (1);
		}
	}
	for (i = 0; i < 10; i++) {
		if (pthread_join(th[i], NULL)) {
			perror("Failed to create thread!");
			return (2);
		}
	}
	printf("\n");
}