/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <nmbabazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 16:38:24 by user42            #+#    #+#             */
/*   Updated: 2021/01/23 14:59:03 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	meal_count(t_philosopher *philo, t_data *data)
{
	philo->meals++;
	if (philo->meals == data->nb_meal)
		sem_post(data->meals);
	return ;
}

void	philo_sleep(t_philosopher *philo, t_data *data)
{
	sem_post(data->fork);
	print_state(philo, data, "is sleeping\n");
	ft_sleep(data->t_sleep * 1000);
}

int		philo_eat(t_philosopher *philo, t_data *data)
{
	sem_wait(data->fork);
	print_state(philo, data, "has taken a fork\n");
	print_state(philo, data, "has taken a fork\n");
	print_state(philo, data, "is eating\n");
	sem_wait(data->end);
	meal_count(philo, data);
	philo->t_start = gettime();
	sem_post(data->end);
	ft_sleep(data->t_eat * 1000);
	return (1);
}

void	*liveness_check(void *philosopher)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)philosopher;
	philo->t_start = gettime();
	while (!g_died)
	{
		philo->t_now = gettime();
		if ((philo->t_now - philo->t_start) >= philo->data->t_die)
		{
			sem_wait(philo->data->end);
			if (!g_died && philo->data->isfull)
			{
				g_died = 1;
				usleep(100);
				print_death(philo, philo->data, "died");
				kill(0, SIGINT);
			}
			sem_post(philo->data->end);
		}
	}
	return (NULL);
}

int		routine(void *philosopher)
{
	t_philosopher	*philo;
	pthread_t		liveness;

	philo = (t_philosopher *)philosopher;
	pthread_create(&liveness, NULL, &liveness_check, philosopher);
	while (!g_died)
	{
		philo_eat(philo, philo->data);
		philo_sleep(philo, philo->data);
		print_state(philo, philo->data, "is thinking\n");
		usleep(100);
	}
	return (1);
}
