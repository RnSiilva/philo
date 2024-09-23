/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:35:42 by resilva           #+#    #+#             */
/*   Updated: 2024/09/21 18:02:48 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/time.h>
#include <semaphore.h>
#include <pthread.h>
#include <fcntl.h>
#include <signal.h>

#define SEM_FORK "/fork"
#define SEM_DEATH "/death"
#define SEM_PRINT "/print"
#define SEM_FINISH "/finish"
#define SEM_SATISFIED "/satisfied"

#define TAKE "has taken a fork"
#define EAT "is eating"
#define SLEEP "is sleeping"
#define THINK "is thinking"
#define DIE "died"
#define NO 0
#define YES 1

typedef struct s_table	t_table;

typedef struct s_philo
{
	int			id;
	int			eat_count;
	long long	last_meal;
	pthread_t	thread;
	pid_t		pid;
	t_table		*table;
}				t_philo;

typedef struct s_table
{
	int			num_of_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			limit_meals;
	long long	time_start;
	t_philo		*philo;
	sem_t		*forks;
	sem_t		*print_sem;
	sem_t		*death_sem;
	sem_t		*satisfied_sem;
	sem_t		*finish_sem;
}				t_table;

typedef enum s_opcode
{
	OPEN,
	CLOSE,
	POST,
	WAIT,
	UNLINK,
}			t_opcode;

void		error_exit(t_table *table, char *msg, int mode);

void		*safe_malloc(t_table *table, size_t bytes);

int			ft_atoi(char *str);
long long	ft_gettime(void);

void		start_dinner(t_philo *philo);
void		finish_dinner(t_table *table);

void		print_action(t_philo *philo, char *action);
void		ft_sleep(long long stop);
