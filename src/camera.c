/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-oiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 23:37:12 by cel-oiri          #+#    #+#             */
/*   Updated: 2020/02/19 23:42:09 by cel-oiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		verif_camera(t_list_pars **l)
{
	t_list_pars	*l2;
	int			i;

	l2 = (*l)->next;
	i = 0;
	while ((l2 != NULL) && (i < 2))
	{
		if ((length_line_nbr(l2->str)) != 3)
		{
			ft_putendl("Wrong format file.");
			return (0);
		}
		i++;
		l2 = l2->next;
	}
	(*l) = l2;
	return (1);
}

void	insert_cam(t_list_pars **lt, t_all *all)
{
	t_vector	lookfrom;
	t_vector	lookat;
	t_list_pars	*l;
	char		**tab;

	l = (*lt)->next;
	tab = ft_strsplit(l->str, ' ');
	lookfrom = (t_vector){ft_atof(tab[0]), ft_atof(tab[1]), ft_atof(tab[2])
		+ 1e-6};
	freedchar(tab);
	l = l->next;
	tab = ft_strsplit(l->str, ' ');
	lookat = (t_vector){ft_atof(tab[0]), ft_atof(tab[1]), ft_atof(tab[2])};
	freedchar(tab);
	init_camera(&(all->cam), lookfrom, lookat);
	l = l->next;
	*lt = l;
}

void	init_camera(t_camera *cam, t_vector lookfrom, t_vector lookat)
{
	cam->lookfrom = lookfrom;
	cam->lookat = lookat;
	cam->vfov = 60.0;
	cam->aspect = (double)WIN_WIDTH / (double)WIN_HEIGHT;
	cam->theta = cam->vfov * M_PI / 180.0;
	cam->half_height = tan(cam->theta / 2);
	cam->half_width = cam->aspect * cam->half_height;
	cam->lookup.x = 0.0;
	cam->lookup.y = 1.0;
	cam->lookup.z = 0.0;
}
