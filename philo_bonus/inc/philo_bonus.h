/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:35:42 by resilva           #+#    #+#             */
/*   Updated: 2024/09/27 21:52:50 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <pthread.h>
#include <fcntl.h>
#include <signal.h>

#define SEM_FORK "/fork"
#define SEM_DEATH "/death"
#define SEM_PRINT "/print"

#define TAKE "has taken a fork"
#define EAT "is eating"
#define SLEEP "is sleeping"
#define THINK "is thinking"
#define DIE "died"
#define NO 0
#define YES 1

typedef struct s_table	t_table;

/**
 * @brief Structure representing a philosopher in the dining problem.
 *
 * @param id            Unique identifier of the philosopher.
 * @param eat_count     Counter tracking how many times the philosopher
 * has eaten.
 * @param last_meal     Timestamp (in milliseconds) of the last time the
 * philosopher ate.
 * @param pid           Process ID associated with the philosopher.
 * @param meal_lock		
 * @param table         Pointer to the table structure, which holds
 * shared data.
 */
typedef struct s_philo
{
	int				id;
	int				eat_count;
	long long		last_meal;
	pid_t			pid;
	pthread_mutex_t	meal_lock;
	t_table			*table;
}				t_philo;

/**
 * @brief Structure representing the table in the dining problem.
 *
 * @param num_of_philo  Total number of philosophers participating.
 * @param time_to_die   Maximum time (in milliseconds) a philosopher can
 * go without eating.
 * @param time_to_eat   Time (in milliseconds) a philosopher
 * spends eating.
 * @param time_to_sleep Time (in milliseconds) a philosopher
 * spends sleeping.
 * @param limit_meals   Maximum number of times each philosopher is
 * allowed to eat (optional).
 * @param time_start    Timestamp (in milliseconds) when the
 * simulation started.
 * @param check_pid     Process ID for the process checking the
 * state of philosophers.
 * @param philo         Array of philosophers.
 * @param forks         Semaphore for the forks
 * (shared resources between philosophers).
 * @param print_sem     Semaphore for managing access to
 * print/logging operations.
 * @param death_sem     Semaphore for signaling a philosopher's death.
 * @param satisfied_sem Semaphore for tracking philosophers that have
 * reached their meal limit.
 * @param finish_sem    Semaphore for signaling the end of the simulation.
 */
typedef struct s_table
{
	int			num_of_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			limit_meals;
	long long	time_start;
	pid_t		check_pid;
	t_philo		*philo;
	sem_t		*forks;
	sem_t		*print_sem;
	sem_t		*death_sem;
}				t_table;

/**
 * @brief Starts the dining simulation for a philosopher.
 *
 * @param philo Pointer to the philosopher structure to start the
 * simulation for.
 */
void		start_dinner(t_philo *philo);

/**
 * @brief Finishes the dining simulation and cleans up resources.
 *
 * @param table Pointer to the table structure containing shared data.
 */
void		finish_dinner(t_table *table);

/**
 * @brief Function to check if all philosophers have eaten enough meals.
 *
 * @param data Pointer to the table structure passed as a void
 * pointer for use in pthreads.
 * @return Always returns NULL after execution.
 */
void		*check_full(void *data);

/**
 * @brief Prints a philosopher's action (eating, sleeping, etc.)
 * in a thread-safe way.
 *
 * @param philo  Pointer to the philosopher performing the action.
 * @param action The action being performed
 * (e.g., "is eating", "is sleeping").
 */
void		print_action(t_philo *philo, char *action);

/**
 * @brief Makes the philosopher sleep for a given duration
 * (in milliseconds).
 *
 * @param stop Time in milliseconds for how long the
 * philosopher should sleep.
 */
void		ft_sleep(long long stop);

/**
 * @brief Convert a string to an integer.
 *
 * @param str The string to convert.
 * @return The integer representation of the string.
 */
int			ft_atoi(char *str);

/**
 * @brief Get the current timestamp in milliseconds.
 *
 * @return The current time in milliseconds since an
 * arbitrary start point.
 */
long long	ft_gettime(void);

/**
 * @brief Print an error message and clean up resources.
 *
 * @param table Pointer to the table structure containing
 * shared data.
 * @param msg   The error message to be displayed.
 * @param mode  Determines the behavior after displaying
 * the error (e.g., exit the program).
 */
void		error_exit(t_table *table, char *msg, int mode);

/**
 * @brief Safely allocate memory and handle errors.
 *
 * @param table Pointer to the table structure, used for
 * error handling.
 * @param bytes Number of bytes to allocate.
 * @return A pointer to the allocated memory, or exits on failure.
 */
void		*safe_malloc(t_table *table, size_t bytes);

/**
 * @brief Check if any philosopher still needs to eat.
 *
 * This function checks if the current philosopher or any other
 * philosopher has not yet finished their meal quota, based on the
 * maximum allowed meals. It returns true if any philosopher is still
 * hungry, otherwise returns false.
 *
 * @param philo Pointer to the philosopher structure to check meal status.
 * @return true if any philosopher still needs to eat, false otherwise.
 */
int			is_someone_hungry(t_philo *philo);
