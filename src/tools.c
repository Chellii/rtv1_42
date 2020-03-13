/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-oiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 00:27:33 by cel-oiri          #+#    #+#             */
/*   Updated: 2020/02/20 00:28:40 by cel-oiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		wrong_format(int v)
{
	if (v == 0)
	{
		ft_putendl("Wrong format file.");
		return (0);
	}
	return (1);
}

void	insert_color(t_vector *vector, char *str)
{
	char **tab;

	tab = ft_strsplit(str, ' ');
	*vector = (t_vector){ft_atof(tab[0]) / 255, ft_atof(tab[1]) / 255,
		ft_atof(tab[2]) / 255};
	freedchar(tab);
}

int		ft_min_ray(double t1, double t2, double *t)
{
	if (((t1 < t2 || t2 < MIN_DIS) && t1 > MIN_DIS) && (t1 < *t))
	{
		*t = t1;
		return (1);
	}
	else if (((t2 < t1 || t1 < MIN_DIS) && t2 > MIN_DIS) && (t2 < *t))
	{
		*t = t2;
		return (1);
	}
	else
		return (0);
}
