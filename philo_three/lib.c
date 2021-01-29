/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <nmbabazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 16:38:24 by user42            #+#    #+#             */
/*   Updated: 2021/01/23 13:37:01 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		str_isdigit(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int		ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int		ft_atoi(const char *nb)
{
	long	resultat;
	int		signe;

	resultat = 0;
	signe = 1;
	while (*nb == 32 || (*nb > 8 && *nb < 14))
		nb++;
	if (*nb == '-' || *nb == '+')
	{
		if (*nb == '-')
			signe = -1;
		nb++;
	}
	while (ft_isdigit(*nb))
	{
		resultat *= 10;
		resultat += (long)*nb - 48;
		nb++;
	}
	if (resultat < 0)
		resultat = (signe < 0) ? 0 : -1;
	return (int)(resultat * signe);
}

void	ft_bzero(void *s, size_t n)
{
	int		i;
	char	*start;

	i = 0;
	start = s;
	while (n)
	{
		start[i] = 0;
		i++;
		n--;
	}
}

void	*ft_calloc(size_t len)
{
	void	*ret;

	if (!(ret = malloc(len)))
		return (NULL);
	ft_bzero(ret, len);
	return (ret);
}
