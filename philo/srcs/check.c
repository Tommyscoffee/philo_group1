/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:44:13 by atomizaw          #+#    #+#             */
/*   Updated: 2022/03/02 22:13:50 by atomizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	is_arg_ok(int argc, char **argv)
{
	int	number_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	must_eat_count;

	if (argc == 5 || argc == 6)
	{
		number_philo = ft_atoi(argv[1]);
		time_die = ft_atoi(argv[2]);
		time_eat = ft_atoi(argv[3]);
		time_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			must_eat_count = ft_atoi(argv[5]);
		else
			must_eat_count = 0;
		if (number_philo < 0 || time_die < 0 || time_eat < 0
			|| time_sleep < 0 || must_eat_count < 0)
			return (FALSE);
		else
			return (TRUE);
	}
	else
		return (FALSE);
}
