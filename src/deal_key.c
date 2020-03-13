/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-oiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 23:42:49 by cel-oiri          #+#    #+#             */
/*   Updated: 2020/02/19 23:42:51 by cel-oiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		deal_key(int key, t_data *w)
{
	if (key == 53)
	{
		mlx_destroy_image(w->mlx_ptr, w->img_ptr);
		mlx_destroy_window(w->mlx_ptr, w->win_ptr);
		exit(1);
	}
	return (0);
}

int		ft_close(void *data)
{
	(void)data;
	exit(0);
	return (0);
}
