/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:43:10 by resilva           #+#    #+#             */
/*   Updated: 2024/09/10 14:01:38 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int	x = 2;

void	*routine()
{
	x++;
	sleep(2);
	printf("Value of x: %d\nProcess id %d\n\n", x, getpid());
}

void	*routine2()
{
	sleep(2);
	printf("Value of x: %d\nProcess id %d\n\n", x, getpid());
}
int	main(void)
{
	pthread_t	t1, t2;
	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_create(&t2, NULL, &routine2, NULL) != 0)
		return (2);
	if (pthread_join(t1, NULL) != 0)
		return (3);
	if (pthread_join(t2, NULL) != 0)
		return (4);
	return (0);
}