/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva < resilva@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 00:50:12 by resilva           #+#    #+#             */
/*   Updated: 2024/09/25 09:47:44 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	clean_table(t_table *table)
{
	if (table->philo)
		free (table->philo);
	if (table->fork_padlock)
		free (table->fork_padlock);
}

static void	destroy_padlocks(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_of_philo)
		pthread_mutex_destroy(&table->fork_padlock[i]);
	clean_table(table);
	pthread_mutex_destroy(&table->print_padlock);
	pthread_mutex_destroy(&table->eat_padlock);
	pthread_mutex_destroy(&table->finish_padlock);
}

int	finish_dinner(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_of_philo)
	{
		if (pthread_join(table->philo[i].thread, NULL))
			return (msg_error(table, "Error: Failed to join thread", 2));
	}
	destroy_padlocks(table);
	return (0);
}

int	msg_error(t_table *table, char *msg, int mode)
{
	if (mode == 1)
		clean_table(table);
	else if (mode == 2)
		destroy_padlocks(table);
	else if (mode == 3)
		finish_dinner(table);
	while (*msg)
		write (2, msg++, sizeof(char));
	write (2, "\n", sizeof(char));
	return (1);
}
