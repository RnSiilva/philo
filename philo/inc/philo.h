/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva < resilva@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 20:26:11 by resilva           #+#    #+#             */
/*   Updated: 2024/09/25 09:50:25 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>
#include <errno.h>

#define TAKE "has taken a fork"
#define EAT "is eating"
#define SLEEP "is sleeping"
#define THINK "is thinking"
#define DIE "died"
#define NO 0
#define YES 1
#define WRONG_INP "Wrong input\nOne or more arguments are invalid!"

typedef struct s_table	t_table;
typedef pthread_mutex_t	t_mtx;

/**
 * @brief Structure representing a philosopher in the dining
 *  problem.
 *
 * @param id            Unique identifier of the philosopher.
 * @param first_fork    Index of the first fork (mutex) the philosopher will
 * try to pick up.
 * @param second_fork   Index of the second fork (mutex) the philosopher will
 * try to pick up.
 * @param count_eat     Counter tracking how many times the philosopher has
 * eaten.
 * @param last_eat      Timestamp (in milliseconds) of the last time the
 * philosopher ate.
 * @param thread        Thread that simulates the philosopher's actions.
 * @param table         Pointer to the table structure, which holds shared data.
 */
typedef struct s_philo
{
	int			id;
	int			first_fork;
	int			second_fork;
	int			count_eat;
	long long	last_eat;
	pthread_t	thread;
	t_table		*table;
}				t_philo;

/**
 * @brief Structure representing the dining table and its shared resources.
 *
 * @param num_of_philo  Number of philosophers sitting at the table.
 * @param time_to_die   Maximum time (in milliseconds) a philosopher can go
 * without eating before dying.
 * @param time_to_eat   Time (in milliseconds) a philosopher spends eating.
 * @param time_to_sleep Time (in milliseconds) a philosopher spends sleeping.
 * @param limit_meals   Maximum number of times each philosopher is allowed
 * to eat. (-1 if unlimited).
 * @param finish_flag   Flag indicating if the simulation should stop (1
 * when finished, 0 otherwise).
 * @param ate_enough    Counter tracking how many philosophers have eaten the
 * required number of meals.
 * @param time_start    Timestamp (in milliseconds) when the simulation started.
 * @param philo         Pointer to an array of philosophers.
 * @param fork_padlock  Array of mutexes, one for each fork, used to lock the
 * forks during use.
 * @param print_padlock Mutex used to synchronize printing to the console to
 * avoid data races.
 * @param eat_padlock   Mutex used to synchronize access to variables related to
 * eating (like `count_eat` and `last_eat`).
 * @param finish_padlock Mutex used to control access to the `finish_flag` to
 * avoid race conditions.
 */
typedef struct s_table
{
	int			num_of_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			limit_meals;
	int			finish_flag;
	int			ate_enough;
	long long	time_start;
	t_philo		*philo;
	t_mtx		*fork_padlock;
	t_mtx		print_padlock;
	t_mtx		eat_padlock;
	t_mtx		finish_padlock;
}				t_table;

// *** DINNER ****

/**
 * @brief Starts the dinner simulation for a philosopher.
 *
 * @param data         Pointer to the philosopher data, used to initialize the
 * philosopher's thread.
 * @return             Pointer to the result of the thread (typically NULL in
 * this case).
 */
void		*start_dinner(void *data);

/**
 * @brief Starts the monitoring process for the table, checking the state of
 * the simulation.
 *
 * @param table        Pointer to the table structure, which holds the shared
 * state and resources.
 */
void		start_monitor(t_table *table);

/**
 * @brief Ends the dinner simulation, performing cleanup and final operations.
 *
 * @param table        Pointer to the table structure, used to access and clean
 * up resources.
 * @return             Returns 0 if success, and 0 if failed.
 */
int			finish_dinner(t_table *table);

/**
 * @brief Checks if it is time to finish the simulation based on the table's
 * finish flag or the given finish parameter.
 *
 * @param table        Pointer to the table structure containing the finish flag.
 * @param finish       Flag indicating whether to force finish
 * (1 for yes, 0 for no).
 * @return             Returns 1 if it is time to finish, otherwise 0.
 */
int			is_time_to_finish(t_table *table, int finish);

// *** UTILS ***

/**
 * @brief Gets the current time in milliseconds since the epoch.
 *
 * @return             The current time in milliseconds.
 */
long long	ft_gettime(void);

/**
 * @brief Converts a string to an integer.
 *
 * @param str          String to be converted.
 * @return             The integer value of the string.
 */
int			ft_atoi(char *str);

/**
 * @brief Prints an action performed by a philosopher,
 * synchronizing access to the console.
 *
 * @param philo        Pointer to the philosopher performing the action.
 * @param action       String describing the action to be printed.
 * 
 */
void		print_action(t_philo *philo, char *action);

/**
 * @brief Pauses the execution of the current thread for a specified duration,
 * checking for termination conditions.
 *
 * @param table        Pointer to the table structure,
 * used to check termination conditions.
 * @param stop         Duration to sleep in milliseconds.
 */
void		ft_sleep(t_table *table, long long stop);

// *** EXIT ***

/**
 * @brief Exits the program with an error message and optionally
 * performs cleanup operations.
 *
 * @param table        Pointer to the table structure, used for cleanup.
 * @param msg          Error message to display.
 * @param mode         Mode of exit, determining whether to perform specific
 * actions on exit.
 */
int			msg_error(t_table *table, char *msg, int mode);
