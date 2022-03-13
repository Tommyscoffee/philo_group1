/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_operation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:10:35 by atomizaw          #+#    #+#             */
/*   Updated: 2022/03/12 15:23:09 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*philo_operate(void *philo_void)
{
	t_philo	*philo;
	long	eat_count;

	eat_count = 0;
	philo = (t_philo *)philo_void;
	if (philo->idx % 2 == 0)
		usleep(200);// ./philo 5 800 200 200で誰かが死なないかワカモレで調整
	while (is_hungry(philo, eat_count))
	{
		if (philo_takeleft(philo))
			return (NULL);
		if (philo_takeright(philo))
			return (NULL);
		// if (philo_takeleft_again(philo))
		// 	return (NULL);//ここがあると./philo 5 800 200 200で13524の順番が崩れて死ぬ
		if (philo_start_eat(philo))
			return (NULL);
		philo_putright(philo);
		philo_putleft(philo);
		if (philo_start_sleep(philo, is_hungry(philo, eat_count + 1)))
			return (NULL);
		eat_count++;
	}
	philo_satisfied(philo);
	return (NULL);
}

void	philo_start(t_philo *nil, long num_philo)
{
	t_philo		*philo;
	pthread_t	*pthread;

	pthread = (pthread_t *)malloc(sizeof(pthread_t *) * num_philo);
	philo = nil->philo_right;
	while (philo != nil)
	{
		if (!pthread_create(&(pthread[philo->idx - 1]),
				NULL, &philo_operate, (void *)philo))
			philo = philo->philo_right;
	}
	monitor_start(nil, num_philo);
	philo = nil->philo_right;
	while (philo != nil)
	{
		pthread_join(pthread[philo->idx - 1], NULL);
		philo = philo->philo_right;
	}
	free(pthread);
}

int	is_hungry(t_philo *philo, int idx)
{
	if (philo->must_eat_count == -1 || idx < philo->must_eat_count)
		return (TRUE);
	else
		return (FALSE);
}
