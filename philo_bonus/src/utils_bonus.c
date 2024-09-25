/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva < resilva@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 21:22:13 by resilva           #+#    #+#             */
/*   Updated: 2024/09/25 08:47:58 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

long long	ft_gettime(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return ((timeval.tv_sec * 1e3) + (timeval.tv_usec / 1e3));
}

int	ft_atoi(char *str)
{
	long	res;

	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
		msg_error(NULL, "Feed me only positive numbers!", 0);
	else if (*str == '+')
		str++;
	res = 0;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			msg_error(NULL, "The input is not a correct digit!", 0);
		res = (res * 10) + (*str++ - 48);
	}
	if (res > INT_MAX)
		msg_error(NULL, "Some value is too big, INT_MAX is the limit!", 0);
	return ((int)res);
}

void	*safe_malloc(t_table *table, size_t bytes)
{
	void	*res;

	res = malloc(bytes);
	if (!res)
		msg_error(table, "Error with malloc!", 1);
	return (res);
}

void	print_action(t_philo *philo, char *action)
{
	long long	timestamp;

	timestamp = ft_gettime() - philo->table->time_start;
	sem_wait(philo->table->print_sem);
	printf("%lld %d %s\n", timestamp, philo->id, action);
	sem_post(philo->table->print_sem);
}

void	ft_sleep(long long stop)
{
	long long	begin;

	begin = ft_gettime();
	while (ft_gettime() - begin < stop)
		usleep(100);
}
