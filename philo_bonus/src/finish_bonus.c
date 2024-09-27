/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 21:31:17 by resilva           #+#    #+#             */
/*   Updated: 2024/09/27 21:59:48 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

static void	ft_putstr(char *str, int fd)
{
	while (*str)
		write (fd, str++, sizeof(char));
}

void	error_exit(t_table *table, char *msg, int mode)
{
	if (mode == 1)
		free(table->philo);
	if (mode == 2)
		finish_dinner(table);
	ft_putstr(msg, STDERR_FILENO);
	ft_putstr("\n", STDERR_FILENO);
	exit (EXIT_FAILURE);
}

void	finish_dinner(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_of_philo)
	{
		pthread_mutex_destroy(&table->philo[i].meal_lock);
		if (table->philo[i].pid != -1)
			kill(table->philo[i].pid, SIGKILL);
	}
	if (table->philo)
		free(table->philo);
	sem_close(table->forks);
	sem_close(table->death_sem);
	sem_close(table->print_sem);
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_DEATH);
	sem_unlink(SEM_PRINT);
}
