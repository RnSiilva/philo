/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 00:50:12 by resilva           #+#    #+#             */
/*   Updated: 2024/09/19 22:42:46 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	clean_table(t_table *table)
{
	free (table->philo);
	free (table->fork_padlock);
}

static void	destroy_padlocks(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_of_philo)
		safe_mutex(table, &table->fork_padlock[i], DESTROY);
	clean_table(table);
	safe_mutex(table, &table->print_padlock, DESTROY);
	safe_mutex(table, &table->eat_padlock, DESTROY);
	safe_mutex(table, &table->finish_padlock, DESTROY);
}

void	finish_dinner(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_of_philo)
		safe_thread(table, &table->philo[i].thread, &table->philo[i], JOIN);
	destroy_padlocks(table);
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
	else if (mode == 2)
		destroy_padlocks(table);
	else if (mode == 3)
		finish_dinner(table);
	ft_putstr(msg, STDERR_FILENO);
	ft_putstr("\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
