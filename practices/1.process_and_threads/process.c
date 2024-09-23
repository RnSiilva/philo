/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:40:41 by resilva           #+#    #+#             */
/*   Updated: 2024/09/10 13:59:48 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int	main(void)
{
	int	x = 2;

	int	pid = fork();
	if (pid == -1)
		return (1);

	if (pid == 0)
		x++;
	sleep(2);
	printf("Value of x: %d\nProcess id %d\n\n", x, getpid());

	if (pid != 0)
		wait (NULL);

	return (0);
}
