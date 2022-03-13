/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 14:51:38 by atomizaw          #+#    #+#             */
/*   Updated: 2022/03/09 22:32:36 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_philo				*philo;
	t_philo				*nil_philo;
	t_info				*info;

	nil_philo = philo_nil_init();
	if (!is_arg_ok(argc, argv))
	{
		free(nil_philo);
		return (0);
	}
	info = (t_info *)malloc(sizeof(t_info));
	argument_set(argc, argv, info);
	philo_init(info, nil_philo);
	philo_start(nil_philo, info->number_philo);
	philo_destory(nil_philo);
	free(nil_philo);
	free(info);
	return (0);
}

void	philo_destory(t_philo *nil)
{
	t_philo			*philo;
	t_philo			*tmp;
	pthread_mutex_t	*mutex_write;
	int				i;

	philo = nil->philo_right;
	mutex_write = philo->mutex_write;
	while (philo != nil)
	{
		tmp = philo;
		pthread_mutex_destroy(tmp->status->mutex);
		free(tmp->status->mutex);
		free(tmp->status);
		pthread_mutex_destroy(tmp->elapsed_time->mutex);
		free(tmp->elapsed_time->mutex);
		free(tmp->elapsed_time);
		pthread_mutex_destroy(tmp->fork_left->mutex);
		free(tmp->fork_left->mutex);
		free(tmp->fork_left);
		philo = philo->philo_right;
		free(tmp);
	}
	free(mutex_write);
}
