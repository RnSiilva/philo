/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   race.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:09:08 by resilva           #+#    #+#             */
/*   Updated: 2024/09/10 14:25:31 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int	mails = 0;

void	*routine()
{
	for (int i = 0; i < 1000000; i++) {
		mails++;
		// read mails
		// increment
		// write mails
	}
}
/* O problema de RACE CONDITION ocorre qnd duas ou mais threads acessam e modificam uma variavel compartilhada (como mails) ao mesmo tempo, causando resultados imprevisiveis. Neste codigo, as threads leem, incrementam e escrevem o valor de mails sem sincronizacao. Isso pode fazer com que o valor final seja incorreto, pois as threads podem sobrescrever as alteracoes umas das outras.*/
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
	printf("Number of mails: %d\n", mails);
	return (0);
}

/* Para gerar o arquivo .s, compilar com a flag '-S':
cc -S -pthread race.c
Entao dentro do arquivo olhamos a funcao routine, e na linha 3 (L3), eh possivel ver a montagem de como mails eh incrementado:

.L3:
	movl	mails(%rip), %eax
	addl	$1, %eax
	movl	%eax, mails(%rip)
	addl	$1, -4(%rbp)

movl: Esta lendo o valor atual de 'mails' para uso.
addl: Esta incrementando o valor lido de mails.
movl: Armazena o novo valor (incrementado).
*/