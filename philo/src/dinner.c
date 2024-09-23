/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 02:07:12 by resilva           #+#    #+#             */
/*   Updated: 2024/09/21 17:59:00 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	is_dead_or_full(t_philo *philo)
{
	safe_mutex(philo->table, &philo->table->eat_padlock, LOCK);
	if (ft_gettime() - philo->last_eat >= (philo->table->time_to_die))
	{
		print_action(philo, DIE);
		is_time_to_finish(philo->table, YES);
		safe_mutex(philo->table, &philo->table->eat_padlock, UNLOCK);
		return (1);
	}
	else if (philo->table->limit_meals > 0 && philo->count_eat >= \
		philo->table->limit_meals)
	{
		philo->table->ate_enough++;
		if (philo->table->ate_enough >= philo->table->num_of_philo)
		{
			is_time_to_finish(philo->table, YES);
			safe_mutex(philo->table, &philo->table->eat_padlock, UNLOCK);
			return (1);
		}
	}
	safe_mutex(philo->table, &philo->table->eat_padlock, UNLOCK);
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

static void	eat(t_table *table, t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		safe_mutex(table, &table->fork_padlock[philo->first_fork], LOCK);
		safe_mutex(table, &table->fork_padlock[philo->second_fork], LOCK);
	}
	else
	{
		safe_mutex(table, &table->fork_padlock[philo->second_fork], LOCK);
		safe_mutex(table, &table->fork_padlock[philo->first_fork], LOCK);
	}
	print_action(philo, TAKE);
	print_action(philo, TAKE);
	print_action(philo, EAT);
	ft_sleep(table, table->time_to_eat);
	safe_mutex(table, &table->eat_padlock, LOCK);
	philo->count_eat++;
	philo->last_eat = ft_gettime();
	safe_mutex(table, &table->eat_padlock, UNLOCK);
	safe_mutex(table, &table->fork_padlock[philo->second_fork], UNLOCK);
	safe_mutex(table, &table->fork_padlock[philo->first_fork], UNLOCK);
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
	if (philo->id % 2 == 0)
		usleep(philo->table->time_to_eat * 1e3);
	while (42)
	{
		if (philo->table->num_of_philo == 1)
		{
			one_philo(philo->table);
			return (0);
		}
		if (is_time_to_finish(philo->table, NO))
			return (0);
		eat(philo->table, philo);
		print_action(philo, SLEEP);
		ft_sleep(philo->table, philo->table->time_to_sleep);
		print_action(philo, THINK);
		if (philo->table->num_of_philo % 2 != 0)
			ft_sleep(philo->table, philo->table->time_to_eat);
	}
	return (0);
}
