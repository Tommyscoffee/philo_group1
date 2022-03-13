/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 22:41:41 by atomizaw          #+#    #+#             */
/*   Updated: 2022/03/12 15:07:35 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	philo_start_eat(t_philo *philo)
{
	struct timeval	now;
	pthread_mutex_t	*mutex_status;
	pthread_mutex_t	*mutex_elapsed_time;

	philo_put_message(philo, EAT);
	//ここで食事を始めた時からの経過時間でdieを検知
	gettimeofday(&now, NULL);
	mutex_elapsed_time = philo->elapsed_time->mutex;
	pthread_mutex_lock(mutex_elapsed_time);
	philo->elapsed_time->ms = now.tv_sec * 1000000 + now.tv_usec;
	pthread_mutex_unlock(mutex_elapsed_time);
	philo_usleep(philo->info->eat);
	mutex_status = philo->status->mutex;
	pthread_mutex_lock(mutex_status);
	if (philo->status->status == DIE)
	{
		pthread_mutex_unlock(mutex_status);
		return (DEAD);
	}
	pthread_mutex_unlock(mutex_status);
	philo_put_message(philo, SLEEP);
	// gettimeofday(&now, NULL);
	// mutex_elapsed_time = philo->elapsed_time->mutex;
	// pthread_mutex_lock(mutex_elapsed_time);
	// philo->elapsed_time->ms = now.tv_sec * 1000000 + now.tv_usec;
	// pthread_mutex_unlock(mutex_elapsed_time);
	return (FALSE);
}
