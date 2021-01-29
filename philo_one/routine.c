/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 16:38:24 by user42            #+#    #+#             */
/*   Updated: 2021/01/24 12:23:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	meal_count(t_philosopher *philo, t_data *data)
{
	philo->meals++;
	if (philo->meals > 0 && philo->meals == data->nb_meal)
	{
		data->isfull--;
		pthread_mutex_lock(&data->write);
		if (!data->isfull && !g_died)
		{
			g_died = 2;
			write(1, "Everyone is full\n", 17);
		}
		pthread_mutex_unlock(&data->write);
	}
}

void	philo_sleep(t_philosopher *philo, t_data *data)
{
	pthread_mutex_unlock(&data->fork[philo->right]);
	pthread_mutex_unlock(&data->fork[philo->left]);
	print_state(philo, data, "is sleeping\n");
	ft_sleep(data->t_sleep * 1000);
}

int		philo_eat(t_philosopher *philo, t_data *data)
{
	pthread_mutex_lock(&data->fork[philo->right]);
	print_state(philo, data, "has taken a fork\n");
	pthread_mutex_lock(&data->fork[philo->left]);
	print_state(philo, data, "has taken a fork\n");
	pthread_mutex_lock(&data->end);
	print_state(philo, data, "is eating\n");
	meal_count(philo, data);
	philo->t_start = gettime();
	pthread_mutex_unlock(&data->end);
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
			pthread_mutex_lock(&philo->data->end);
			if (!g_died && philo->data->isfull)
			{
				g_died = 1;
				usleep(100);
				print_death(philo, philo->data, "died\n");
			}
			pthread_mutex_unlock(&philo->data->end);
		}
	}
	return (NULL);
}

void	*routine(void *philosopher)
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
	return (NULL);
}
