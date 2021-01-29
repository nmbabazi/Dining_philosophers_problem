/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <nmbabazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 14:42:49 by user42            #+#    #+#             */
/*   Updated: 2021/01/23 13:38:29 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philosopher(t_philosopher *philosopher, t_data *data)
{
	int i;

	i = 0;
	while (i < data->nb_philo)
	{
		philosopher[i].data = data;
		philosopher[i].id = i;
		philosopher[i].meals = 0;
		i++;
	}
}

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
	sem_close(data->fork);
	sem_close(data->write);
	sem_close(data->end);
	sem_close(data->meals);
	free(philosopher);
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
	creat_process(philosopher, &data);
	ft_clear(philosopher, &data);
	return (0);
}
