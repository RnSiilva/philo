/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva < resilva@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 20:55:59 by resilva           #+#    #+#             */
/*   Updated: 2024/09/25 09:47:53 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long long	ft_gettime(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return ((timeval.tv_sec * 1e3) + (timeval.tv_usec / 1e3));
}

int	ft_atoi(char *str)
{
	long	num;

	num = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (-1);
		num = (num * 10) + (*str++ - 48);
	}
	if (num > INT_MAX)
		return (-1);
	return ((int)num);
}

int	is_time_to_finish(t_table *table, int finish)
{
	pthread_mutex_lock(&table->finish_padlock);
	if (finish || table->finish_flag)
	{
		if (finish)
			table->finish_flag = 1;
		pthread_mutex_unlock(&table->finish_padlock);
		return (1);
	}
	pthread_mutex_unlock(&table->finish_padlock);
	return (0);
}

void	print_action(t_philo *philo, char *action)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->table->print_padlock);
	if (!is_time_to_finish(philo->table, NO))
	{
		timestamp = ft_gettime() - philo->table->time_start;
		printf("%lld %d %s\n", timestamp, philo->id, action);
	}
	pthread_mutex_unlock(&philo->table->print_padlock);
}

void	ft_sleep(t_table *table, long long stop)
{
	long long	begin;

	begin = ft_gettime();
	while (!is_time_to_finish(table, NO) && (ft_gettime() - begin < stop))
		usleep(100);
}
