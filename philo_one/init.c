/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <nmbabazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 14:42:49 by user42            #+#    #+#             */
/*   Updated: 2021/01/24 13:35:43 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		creat_thread(t_philosopher *philosopher, t_data *data)
{
	int i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&philosopher[i].thread, NULL, &routine,
			(void *)(philosopher + i)) != 0)
			return (print_error("Failed to create thread\n"));
		i++;
		i++;
	}
	usleep(1000);
	i = 1;
	while (i < data->nb_philo)
	{
		if (pthread_create(&philosopher[i].thread, NULL, &routine,
			(void *)(philosopher + i)) != 0)
			return (print_error("Failed to create thread\n"));
		i++;
		i++;
	}
	return (1);
}

int		start_threads(t_philosopher *philosopher, t_data *data)
{
	int i;

	i = 0;
	data->timer_start = gettime();
	if (!creat_thread(philosopher, data))
		return (0);
	while (i < data->nb_philo && !g_died)
	{
		if (pthread_join(philosopher[i].thread, NULL) != 0)
			return (print_error("Failed to join thread\n"));
		i++;
	}
	return (1);
}

void	init_philosopher(t_philosopher *philosopher, t_data *data)
{
	int i;

	i = 0;
	while (i < data->nb_philo)
	{
		philosopher[i].data = data;
		philosopher[i].id = i;
		philosopher[i].meals = 0;
		philosopher[i].right = i;
		philosopher[i].left = (i + 1) % data->nb_philo;
		i++;
	}
}

int		init_data(t_data *data, char **av)
{
	int i;

	i = 0;
	data->nb_philo = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	data->isfull = data->nb_philo;
	if (av[5])
		data->nb_meal = ft_atoi(av[5]);
	else
		data->nb_meal = -1;
	if (!(data->fork = ft_calloc(sizeof(pthread_mutex_t) * data->nb_philo)))
		return (print_error("calloc failed\n"));
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->fork[i++], NULL);
	}
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->end, NULL);
	return (1);
}
