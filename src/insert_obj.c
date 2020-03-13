/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-oiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 20:07:15 by cel-oiri          #+#    #+#             */
/*   Updated: 2020/02/19 23:44:59 by cel-oiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	insert_vector(t_vector *vector, char *str)
{
	char **tab;

	tab = ft_strsplit(str, ' ');
	*vector = (t_vector){ft_atof(tab[0]), ft_atof(tab[1]), ft_atof(tab[2])};
	freedchar(tab);
}

void	insert_sph(t_list_pars **lt, t_all *all)
{
	t_list_pars	*l;
	t_obj		s;

	ft_memset(&s, 0, sizeof(t_obj));
	s.type = SPHERE;
	l = (*lt)->next;
	insert_vector(&s.pos, l->str);
	l = l->next;
	s.radius = ft_atof(l->str);
	l = l->next;
	insert_color(&(s.material.diffuse), l->str);
	l = l->next;
	insert_vector(&s.trans, l->str);
	l = l->next;
	insert_vector(&s.rot, l->str);
	ft_add_obj_back(&(all->obj), ft_obj_new(s));
	(*lt) = l;
}

void	insert_plane(t_list_pars **lt, t_all *all)
{
	t_list_pars	*l;
	t_obj		s;

	ft_memset(&s, 0, sizeof(t_obj));
	s.type = PLANE;
	l = (*lt)->next;
	insert_vector(&s.pos, l->str);
	l = l->next;
	insert_vector(&s.normal, l->str);
	l = l->next;
	insert_color(&(s.material.diffuse), l->str);
	l = l->next;
	insert_vector(&s.trans, l->str);
	l = l->next;
	insert_vector(&s.rot, l->str);
	ft_add_obj_back(&(all->obj), ft_obj_new(s));
	*lt = l;
}

void	insert_cone(t_list_pars **lt, t_all *all)
{
	t_list_pars	*l;
	t_obj		s;

	ft_memset(&s, 0, sizeof(t_obj));
	s.type = CONE;
	l = (*lt)->next;
	insert_vector(&s.pos, l->str);
	l = l->next;
	insert_vector(&s.axis, l->str);
	l = l->next;
	s.angle = ft_atof(l->str);
	l = l->next;
	insert_color(&(s.material.diffuse), l->str);
	l = l->next;
	insert_vector(&s.trans, l->str);
	l = l->next;
	insert_vector(&s.rot, l->str);
	ft_add_obj_back(&(all->obj), ft_obj_new(s));
	(*lt) = l;
}

void	insert_cylinder(t_list_pars **lt, t_all *all)
{
	t_list_pars	*l;
	t_obj		s;

	ft_memset(&s, 0, sizeof(t_obj));
	s.type = CYLINDER;
	l = (*lt)->next;
	insert_vector(&s.pos, l->str);
	l = l->next;
	insert_vector(&s.axis, l->str);
	l = l->next;
	s.radius = ft_atof(l->str);
	l = l->next;
	insert_color(&(s.material.diffuse), l->str);
	l = l->next;
	insert_vector(&s.trans, l->str);
	l = l->next;
	insert_vector(&s.rot, l->str);
	ft_add_obj_back(&(all->obj), ft_obj_new(s));
	(*lt) = l;
}
