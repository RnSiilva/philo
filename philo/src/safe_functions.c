/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 21:52:40 by resilva           #+#    #+#             */
/*   Updated: 2024/09/19 23:00:16 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*safe_malloc(t_table *table, size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
		error_exit(table, "Error with the malloc", 0);
	return (ret);
}

static void	handle_mutex_error(t_table *table, t_opcode opcode, int status)
{
	if (opcode == 0)
		return ;
	if (status == EINVAL && \
		(opcode == LOCK || opcode == UNLOCK || opcode == DESTROY))
		error_exit(table, "The value specified by mutex is invalid.", 2);
	else if (status == EINVAL && opcode == INIT)
		error_exit(table, "The value specified by attr is invalid.", 2);
	else if (status == EPERM && opcode == UNLOCK)
		error_exit(table, \
			"The current thread does not hold a lock on mutex.", 2);
	else if (status == EDEADLK && opcode == LOCK)
		error_exit(table, "A deadlock would occur if the thread blocked" \
			"waiting for mutex.", 2);
	else if (status == ENOMEM && opcode == INIT)
		error_exit(table, "The process cannot allocate enough memory to" \
			"create another mutex.", 2);
	else if (status == EBUSY && opcode == DESTROY)
		error_exit(table, "Mutex is locked.", 2);
}

void	safe_mutex(t_table *table, t_mtx *mutex, t_opcode opcode)
{
	if (opcode == INIT)
		handle_mutex_error(table, opcode, pthread_mutex_init(mutex, NULL));
	else if (opcode == LOCK)
		handle_mutex_error(table, opcode, pthread_mutex_lock(mutex));
	else if (opcode == UNLOCK)
		handle_mutex_error(table, opcode, pthread_mutex_unlock(mutex));
	else if (opcode == DESTROY)
		handle_mutex_error(table, opcode, pthread_mutex_destroy(mutex));
	else
		error_exit(table, "Wrong opcode for mutex handle", 2);
}

static void	handle_thread_error(t_table *table, int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		error_exit(table, "No resources to create another thread.", 3);
	else if (status == EPERM)
		error_exit(table, \
			"The caller does not have appropriate permission.", 3);
	else if (status == EINVAL && opcode == CREATE)
		error_exit(table, "The value specified by attr is invalid.", 3);
	else if (status == EINVAL && opcode == JOIN)
		error_exit(table, "The value specified by thread is not joinable.", 3);
	else if (status == ESRCH)
		error_exit(table, "No thread could be found corresponding to that"
			" specified by the given thread ID, thread.", 3);
	else if (status == EDEADLK)
		error_exit(table, "A deadlock was detected or the value of"
			" thread specifies the calling thread.", 3);
}

void	safe_thread(t_table *table, \
	pthread_t *thread, void *data, t_opcode opcode)
{
	if (opcode == CREATE)
		handle_thread_error(table, \
			pthread_create(thread, NULL, start_dinner, data), opcode);
	else if (opcode == JOIN)
		handle_thread_error(table, pthread_join(*thread, NULL), opcode);
	else
		error_exit(table, "Wrong opcode for thread handle:"
			" use <CREATE> <JOIN> <DETACH>", 3);
}
