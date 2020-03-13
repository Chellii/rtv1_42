/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-oiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 23:20:22 by cel-oiri          #+#    #+#             */
/*   Updated: 2020/03/09 21:55:09 by cel-oiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

void	graph(t_data *w, t_all *all)
{
	int		i;
	int		j;
	t_ray	r;
	t_hit	hit;

	i = 0;
	hit.hit = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			r = get_ray((double)j / (double)WIN_WIDTH, (double)i /
				(double)WIN_HEIGHT, &all->cam);
			hit = ray_primary_intersection(all, &r);
			if (hit.hit)
				w->data[(WIN_HEIGHT - i - 1) * WIN_WIDTH + j] =
					shade(all, &hit);
			j++;
		}
		i++;
	}
}

int		main(int ac, char **av)
{
	t_data	w;
	t_all	*all;

	if (ac == 2)
	{
		all = ft_all(av[1]);
		w.mlx_ptr = mlx_init();
		w.win_ptr = mlx_new_window(w.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "RTV1");
		w.img_ptr = mlx_new_image(w.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
		w.data = (int *)mlx_get_data_addr(w.img_ptr, &w.b, &w.s_l, &w.end);
		graph(&w, all);
		mlx_put_image_to_window(w.mlx_ptr, w.win_ptr, w.img_ptr, 0, 0);
		mlx_hook(w.win_ptr, 2, 0, &deal_key, &w);
		mlx_hook(w.win_ptr, 17, 0, ft_close, &w);
		mlx_loop(w.mlx_ptr);
		free_all(all);
	}
	else
		ft_putendl("./rtv1 namefile");
	return (0);
}
