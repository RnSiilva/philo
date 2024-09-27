/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 23:18:01 by resilva           #+#    #+#             */
/*   Updated: 2024/09/27 21:44:36 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

static void	take_fork(t_philo *philo);

static void	eat(t_philo *philo)
{
	sem_wait(philo->table->death_sem);
	philo->last_meal = ft_gettime();
	philo->eat_count++;
	if (is_someone_hungry(philo))
		print_action(philo, EAT);
	sem_post(philo->table->death_sem);
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
		pthread_mutex_lock(&philo->meal_lock);
		if ((ft_gettime() - philo->last_meal) \
			>= (philo->table->time_to_die))
		{
			print_action(philo, DIE);
			pthread_mutex_unlock(&philo->meal_lock);
			exit(0);
		}
		pthread_mutex_unlock(&philo->meal_lock);
		if (!is_someone_hungry(philo))
		{
			print_action(philo, EAT);
			exit(0);
		}
		sem_post(philo->table->death_sem);
	}
	return (NULL);
}

void	start_dinner(t_philo *philo)
{
	pthread_t	death;

	pthread_create(&death, NULL, check_death, philo);
	pthread_detach(death);
	if (philo->id % 2 == 0)
		usleep(philo->table->time_to_eat / 2 * 1000);
	while (42)
	{
		take_fork(philo);
		eat(philo);
		print_action(philo, SLEEP);
		usleep(philo->table->time_to_sleep * 1e3);
		print_action(philo, THINK);
		if (philo->table->num_of_philo % 2 != 0)
			ft_sleep(philo->table->time_to_eat);
	}
}
