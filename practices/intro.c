/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.intro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:32:56 by resilva           #+#    #+#             */
/*   Updated: 2024/09/10 13:37:44 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void	*routine()
{
	printf("Starting thread\n");
	sleep(3);
	printf("Ending thread\n");
}
/* 
1.THREAD: Ponteiro p/ armazenar o identificador da nova thread criada.
2.ATTR: Atributos da thread (como prioridade); pode ser NULL p/ usar os atributos padrao.
3.START_ROUTINE: Funcao que a thread ira executar.
4.ARG: Argumento p/ a funcao (pode ser NULL se n houver argumento).

A FUNCAO RETORNA 0 EM CASO DE SUCESSO, E UM VALOR DIFERENTE SE FALHAR.

'-pthread' para compilar o programa
*/
int	main(void)
{
	pthread_t	t1, t2;
	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return (2);
	if (pthread_join(t1, NULL) != 0)
		return (3);
	if (pthread_join(t2, NULL) != 0)
		return (4);
	return (0);
}
