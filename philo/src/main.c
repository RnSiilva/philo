/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva < resilva@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 20:43:18 by resilva           #+#    #+#             */
/*   Updated: 2024/09/25 09:52:01 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	philo_to_thread(t_table *table)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&table->finish_padlock);
	while (++i < table->num_of_philo)
	{
		if (pthread_create(&table->philo[i].thread, NULL, \
			start_dinner, &table->philo[i]))
			return (msg_error(table, "Error: Failed to create thread", 3));
	}
	pthread_mutex_unlock(&table->finish_padlock);
	return (0);
}

static int	init_padlocks(t_table *table)
{
	int	i;
	int	status_err;

	i = -1;
	status_err = 0;
	while (++i < table->num_of_philo)
		status_err = pthread_mutex_init(&table->fork_padlock[i], NULL);
	status_err = pthread_mutex_init(&table->print_padlock, NULL);
	status_err = pthread_mutex_init(&table->eat_padlock, NULL);
	status_err = pthread_mutex_init(&table->finish_padlock, NULL);
	if (status_err != 0)
		return (msg_error(table, "Error: Failed with mutex", 2));
	return (0);
}

static int	init_philosophers(t_table *table)
{
	int		i;
	t_philo	*philo;

	table->philo = NULL;
	table->fork_padlock = NULL;
	table->philo = malloc(sizeof(t_philo) * table->num_of_philo);
	table->fork_padlock = malloc(sizeof(t_mtx) * table->num_of_philo);
	if (!table->philo || !table->fork_padlock)
		return (msg_error(table, "Error: Failed with malloc", 1));
	table->time_start = ft_gettime();
	table->finish_flag = 0;
	i = -1;
	while (++i < table->num_of_philo)
	{
		philo = table->philo + i;
		philo->id = i + 1;
		philo->first_fork = i;
		philo->second_fork = (i + 1) % table->num_of_philo;
		philo->count_eat = 0;
		philo->last_eat = table->time_start;
		philo->table = table;
	}
	return (0);
}

static int	parse(t_table *table, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (msg_error(table, "Wrong input\n" \
				"Usage: ./philo 'num_philo' 'time_die' 'time_eat' 'time_sleep'"
				" 'limit_meals'", 0));
	table->num_of_philo = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		table->limit_meals = ft_atoi(av[5]);
		if (table->limit_meals == 0)
			return (msg_error(table, WRONG_INP, 0));
	}
	else
		table->limit_meals = -1;
	if (table->num_of_philo < 1 || table->time_to_die < 1 \
		|| table->time_to_eat < 1 || table->time_to_sleep < 1)
		return (msg_error(table, WRONG_INP, 0));
	return (0);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (parse(&table, ac, av))
		return (1);
	if (init_philosophers(&table))
		return (1);
	if (init_padlocks(&table))
		return (1);
	if (philo_to_thread(&table))
		return (1);
	start_monitor(&table);
	return (0);
}
