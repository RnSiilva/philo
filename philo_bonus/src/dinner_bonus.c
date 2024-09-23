/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 23:18:01 by resilva           #+#    #+#             */
/*   Updated: 2024/09/21 18:01:21 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

static void	take_fork(t_philo *philo);

static void	eat(t_philo *philo)
{
	print_action(philo, EAT);
	//sem_wait(philo->table->death_sem);
	philo->last_meal = ft_gettime();
	//sem_post(philo->table->death_sem);
	philo->eat_count++;
	if ((philo->table->limit_meals != -1) && \
		(philo->eat_count == philo->table->limit_meals))
	{
		ft_sleep(philo->table->time_to_eat);
		sem_post(philo->table->forks);
		sem_post(philo->table->forks);
		sem_post(philo->table->satisfied_sem);
		return ;
	}
	ft_sleep(philo->table->time_to_eat);
	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
}

static void	take_fork(t_philo *philo)
{
	sem_wait(philo->table->forks);
	print_action(philo, TAKE);
	sem_wait(philo->table->forks);
	print_action(philo, TAKE);
}

void	*check_death(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (42)
	{
		sem_wait(philo->table->death_sem);
		if ((ft_gettime() - philo->last_meal) \
			>= (philo->table->time_to_die))
		{
			sem_wait(philo->table->print_sem);
			printf("%lld %d %s\n", \
				ft_gettime() - philo->table->time_start, philo->id, DIE);
			sem_post(philo->table->finish_sem);
			//sem_post(philo->table->death_sem);
			break ;
		}
		sem_post(philo->table->death_sem);
		usleep(5);
	}
	return (NULL);
}

void	start_dinner(t_philo *philo)
{
	pthread_t	death;

	pthread_create(&death, NULL, check_death, philo);
	pthread_detach(death);
	while (42)
	{
		take_fork(philo);
		eat(philo);
		print_action(philo, SLEEP);
		usleep(philo->table->time_to_sleep * 1e3);
		print_action(philo, THINK);
	}
}
