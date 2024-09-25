/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva < resilva@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:37:19 by resilva           #+#    #+#             */
/*   Updated: 2024/09/25 10:29:40 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	philo_to_process(t_table *table)
{
	int			i;
	pthread_t	death;

	table->time_start = ft_gettime();
	i = -1;
	if (table->limit_meals == 0)
		return ;
	while (++i < table->num_of_philo)
	{
		table->philo[i].pid = fork();
		if (table->philo[i].pid == 0)
			start_dinner(&table->philo[i]);
		else if (table->philo[i].pid < 0)
			msg_error(table, "Error: Fork failed", 2);
	}
	if (table->limit_meals != -1 && \
		pthread_create(&death, NULL, &check_full, table))
		msg_error(table, "Error: Thread Failed.", 2);
	sem_wait(table->finish_sem);
	if (table->limit_meals != -1 && pthread_detach(death))
		msg_error(table, "Error: Thread Failed.", 2);
}

void	init_semaphores(t_table *table)
{
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_DEATH);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_FINISH);
	sem_unlink(SEM_SATISFIED);
	table->forks = sem_open(SEM_FORK, O_CREAT, 0644, table->num_of_philo);
	table->death_sem = sem_open(SEM_DEATH, O_CREAT, 0644, 1);
	table->print_sem = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
	table->finish_sem = sem_open(SEM_FINISH, O_CREAT, 0644, 1);
	table->satisfied_sem = sem_open(SEM_SATISFIED, O_CREAT, 0644, 0);
	sem_wait(table->finish_sem);
}

void	init_philosophers(t_table *table)
{
	int		i;
	t_philo	*philo;

	table->philo = NULL;
	table->philo = safe_malloc(table, sizeof(t_philo) * table->num_of_philo);
	table->time_start = ft_gettime();
	table->check_pid = -1;
	i = -1;
	while (++i < table->num_of_philo)
	{
		philo = table->philo + i;
		philo->id = i + 1;
		philo->last_meal = table->time_start;
		philo->eat_count = 0;
		philo->pid = -1;
		philo->table = table;
	}
}

void	parse(t_table *table, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		msg_error(NULL, "Wrong input", 0);
	table->num_of_philo = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		table->limit_meals = ft_atoi(av[5]);
		if (table->limit_meals == 0)
			exit(EXIT_SUCCESS);
	}
	else
		table->limit_meals = -1;
	if (table->num_of_philo < 1 || table->time_to_die < 1 || \
		table->time_to_eat < 1 || table->time_to_sleep < 1)
		msg_error(table, "Error: "
			"One or more arguments are zero.", 0);
}

int	main(int ac, char **av)
{
	t_table	table;

	parse(&table, ac, av);
	init_philosophers(&table);
	init_semaphores(&table);
	philo_to_process(&table);
	finish_dinner(&table);
	waitpid(-1, NULL, 0);
}
