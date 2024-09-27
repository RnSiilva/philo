/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:44:50 by resilva           #+#    #+#             */
/*   Updated: 2024/09/27 21:44:06 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

static int	is_hungry(t_philo *philo)
{
	int	ret;

	if (philo->table->limit_meals == -1)
		return (1);
	pthread_mutex_lock(&philo->meal_lock);
	ret = philo->eat_count <= philo->table->limit_meals;
	pthread_mutex_unlock(&philo->meal_lock);
	return (ret);
}

static int	is_last_philo(t_philo *philo)
{
	return (philo->id == philo->table->num_of_philo - 1);
}

int	is_someone_hungry(t_philo *philo)
{
	return (!is_last_philo(philo) || is_hungry(philo));
}
