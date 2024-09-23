/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 20:43:18 by resilva           #+#    #+#             */
/*   Updated: 2024/09/21 17:59:30 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	philo_to_thread(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_of_philo)
		safe_thread(table, &table->philo[i].thread, &table->philo[i], CREATE);
}

static void	init_padlocks(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_of_philo)
		safe_mutex(table, &table->fork_padlock[i], INIT);
	safe_mutex(table, &table->print_padlock, INIT);
	safe_mutex(table, &table->eat_padlock, INIT);
	safe_mutex(table, &table->finish_padlock, INIT);
}

static void	init_philosophers(t_table *table)
{
	int		i;
	t_philo	*philo;

	table->philo = safe_malloc(table, (sizeof(t_philo) * table->num_of_philo));
	table->fork_padlock = safe_malloc(table, \
		(sizeof(t_mtx) * table->num_of_philo));
	table->time_start = ft_gettime();
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
}

static void	parse(t_table *table, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		error_exit(table, "Wrong input\n" \
			"Usage: ./philo 'num_philo' 'time_die' 'time_eat' 'time_sleep'"
			" 'limit_meals'", 0);
	table->num_of_philo = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		table->limit_meals = ft_atoi(av[5]);
		if (table->limit_meals == 0)
			exit(EXIT_FAILURE);
	}
	else
		table->limit_meals = -1;
	table->finish_flag = 0;
}

int	main(int ac, char **av)
{
	t_table	table;

	parse(&table, ac, av);
	init_philosophers(&table);
	init_padlocks(&table);
	philo_to_thread(&table);
	start_monitor(&table);
}
