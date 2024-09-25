/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva < resilva@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 02:07:12 by resilva           #+#    #+#             */
/*   Updated: 2024/09/25 08:46:13 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	is_dead_or_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->eat_padlock);
	if (ft_gettime() - philo->last_eat >= (philo->table->time_to_die))
	{
		print_action(philo, DIE);
		is_time_to_finish(philo->table, YES);
		pthread_mutex_unlock(&philo->table->eat_padlock);
		return (1);
	}
	else if (philo->table->limit_meals > 0 && philo->count_eat >= \
		philo->table->limit_meals)
	{
		philo->table->ate_enough++;
		if (philo->table->ate_enough >= philo->table->num_of_philo)
		{
			is_time_to_finish(philo->table, YES);
			pthread_mutex_unlock(&philo->table->eat_padlock);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->table->eat_padlock);
	return (0);
}

void	start_monitor(t_table *table)
{
	int	i;
	int	cont;

	cont = 42;
	while (cont)
	{
		i = -1;
		table->ate_enough = 0;
		while (++i < table->num_of_philo)
			if (cont && is_dead_or_full(&table->philo[i]))
				cont = 0;
		usleep(10);
	}
	finish_dinner(table);
}

static int	eat(t_table *table, t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&table->fork_padlock[philo->first_fork]);
		pthread_mutex_lock(&table->fork_padlock[philo->second_fork]);
	}
	else
	{
		pthread_mutex_lock(&table->fork_padlock[philo->second_fork]);
		pthread_mutex_lock(&table->fork_padlock[philo->first_fork]);
	}
	print_action(philo, TAKE);
	print_action(philo, TAKE);
	print_action(philo, EAT);
	pthread_mutex_lock(&table->eat_padlock);
	philo->count_eat++;
	philo->last_eat = ft_gettime();
	pthread_mutex_unlock(&table->eat_padlock);
	ft_sleep(table, table->time_to_eat);
	pthread_mutex_unlock(&table->fork_padlock[philo->second_fork]);
	pthread_mutex_unlock(&table->fork_padlock[philo->first_fork]);
	return (!is_time_to_finish(table, NO));
}

void	one_philo(t_table *table)
{
	print_action(&table->philo[0], TAKE);
	ft_sleep(table, table->time_to_die);
	print_action(&table->philo[0], DIE);
	is_time_to_finish(table, YES);
}

void	*start_dinner(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->table->finish_padlock);
	pthread_mutex_unlock(&philo->table->finish_padlock);
	if (philo->id % 2 == 0)
		usleep(philo->table->time_to_eat * 1e3);
	while (42)
	{
		if (philo->table->num_of_philo == 1)
		{
			one_philo(philo->table);
			break ;
		}
		if (is_time_to_finish(philo->table, NO))
			break ;
		eat(philo->table, philo);
		print_action(philo, SLEEP);
		ft_sleep(philo->table, philo->table->time_to_sleep);
		print_action(philo, THINK);
		if (philo->table->num_of_philo % 2 != 0)
			ft_sleep(philo->table, philo->table->time_to_eat);
	}
	return (0);
}
