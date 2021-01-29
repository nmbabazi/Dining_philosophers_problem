/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 14:42:49 by user42            #+#    #+#             */
/*   Updated: 2021/01/24 12:20:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		pars_arg(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (print_error("wrong number off arguments\n"));
	if (str_isdigit(av[1]) == 0 || str_isdigit(av[2]) == 0
		|| str_isdigit(av[3]) == 0 || str_isdigit(av[4]) == 0)
		return (print_error("wrong arguments\n"));
	if (ft_atoi(av[1]) < 2 || ft_atoi(av[2]) <= 0
		|| ft_atoi(av[3]) <= 0 || ft_atoi(av[4]) <= 0)
		return (print_error("wrong arguments\n"));
	if (av[5] && (str_isdigit(av[5]) == 0 || ft_atoi(av[5]) <= 0))
		return (print_error("wrong arguments\n"));
	return (1);
}

void	ft_clear(t_philosopher *philosopher, t_data *data)
{
	int i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->end);
	free(philosopher);
	free(data->fork);
}

int		main(int ac, char **av)
{
	t_data			data;
	t_philosopher	*philosopher;

	memset(&data, 0, sizeof(t_data));
	if (pars_arg(ac, av) == 0)
		return (-1);
	if (init_data(&data, av) == 0)
		return (-1);
	if (!(philosopher = ft_calloc(sizeof(t_philosopher) * data.nb_philo)))
		return (print_error("calloc failed\n"));
	init_philosopher(philosopher, &data);
	data.timer_start = gettime();
	if (start_threads(philosopher, &data) == 0)
	{
		ft_clear(philosopher, &data);
		return (-1);
	}
	ft_clear(philosopher, &data);
	return (0);
}
