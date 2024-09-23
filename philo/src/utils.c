/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 20:55:59 by resilva           #+#    #+#             */
/*   Updated: 2024/09/21 18:00:25 by resilva          ###   ########.fr       */
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
		error_exit(NULL, "Feed me only positive numbers!", 0);
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			error_exit(NULL, "The input is not a correct digit!", 0);
		num = (num * 10) + (*str++ - 48);
	}
	if (num > INT_MAX)
		error_exit(NULL, "Some value is too big, INT_MAX is the limit!", 0);
	return ((int)num);
}

void	print_action(t_philo *philo, char *action)
{
	long long	timestamp;

	safe_mutex(philo->table, &philo->table->print_padlock, LOCK);
	if (!is_time_to_finish(philo->table, NO))
	{
		timestamp = ft_gettime() - philo->table->time_start;
		printf("%lld %d %s\n", timestamp, philo->id, action);
	}
	safe_mutex(philo->table, &philo->table->print_padlock, UNLOCK);
}

int	is_time_to_finish(t_table *table, int finish)
{
	safe_mutex(table, &table->finish_padlock, LOCK);
	if (finish || table->finish_flag)
	{
		if (finish)
			table->finish_flag = 1;
		safe_mutex(table, &table->finish_padlock, UNLOCK);
		return (1);
	}
	safe_mutex(table, &table->finish_padlock, UNLOCK);
	return (0);
}

void	ft_sleep(t_table *table, long long stop)
{
	long long	begin;

	begin = ft_gettime();
	while (!is_time_to_finish(table, NO) && (ft_gettime() - begin < stop))
		usleep(100);
}
