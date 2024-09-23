/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 03:23:58 by resilva           #+#    #+#             */
/*   Updated: 2024/09/20 03:53:09 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

/**
 * @brief A funcao de rotina passada para pthread_create para ser percorrida paralelamente por threads, retorna void *, e este valor pode ser acessado atraves do segundo argumento para a funcao pthread_join.
 * 
 */

/**
 * @brief Precisamos alocar a variavel que sera retornada, ja que nao podemos simplesmente retornar uma referencia que sera desalocada no final da funcao (caso n tenha sido alocada com malloc). Entao alocamos para que a referencia continue acessiva mesmo depois da funcao ter acabado.
 * 
 * @return void* O valor retornado pode ser acessado atraves do segundo argumento da funcao pthread_join 
 */
void	*roll_dice()
{
	int value;
	int	*res;

	value = (rand() % 6) + 1;

	res = malloc(sizeof(int));
	if (!res)
		exit(EXIT_FAILURE);
	*res = value;

	printf("Thread result: %p\n\n", res);
	return ((void *)res);
}

int	main(void)
{
	pthread_t	th;
	int			*res;
	
	srand(time(NULL));

	if (pthread_create(&th, NULL, &roll_dice, NULL)) {
		perror("Failed to create thread!");
		return (1);
	}
	if (pthread_join(th, (void **)&res)) {
		perror("Failed to join thread!");
		return (2);
	}
	printf("Main result: %p\n", res);
	printf("Result: %d\n", *res);
	free(res);
}
