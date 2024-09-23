/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 21:31:17 by resilva           #+#    #+#             */
/*   Updated: 2024/09/21 18:01:24 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

static void	clean_table(t_table *table)
{
	(void)table;
}

static void	ft_putstr(char *str, int fd)
{
	while (*str)
		write (fd, str++, sizeof(char));
}

void	error_exit(t_table *table, char *msg, int mode)
{
	if (mode == 1)
		clean_table(table);
	ft_putstr(msg, STDERR_FILENO);
	ft_putstr("\n", STDERR_FILENO);
	exit (EXIT_FAILURE);
}

void	finish_dinner(t_table *table)
{
	int	i;

	if (table->limit_meals != 0)
	{
		i = -1;
		while (++i < table->num_of_philo)
			kill(table->philo[i].pid, SIGKILL);
	}
	sem_close(table->forks);
	sem_close(table->death_sem);
	sem_close(table->print_sem);
	sem_close(table->finish_sem);
	sem_close(table->satisfied_sem);
	sem_unlink(SEM_SATISFIED);
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_DEATH);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_FINISH);
	sem_unlink(SEM_SATISFIED);
	free(table->philo);
}
