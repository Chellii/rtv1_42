/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_fct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-oiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 23:45:01 by cel-oiri          #+#    #+#             */
/*   Updated: 2020/02/26 23:45:02 by cel-oiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	hit_sphere(t_hit *hit, t_obj *new, t_ray r)
{
	hit->hit = 1;
	hit->p = vector_add(r.start, vector_scale(r.dir, hit->t));
	hit->n = vector_normalize(vector_sub(hit->p, new->pos));
	if (vector_dot(hit->n, r.dir) > 0.0)
		hit->n = vector_scale(hit->n, -1);
	hit->m = new->material;
}

void	hit_plan(t_hit *hit, t_obj *new, t_ray r)
{
	hit->hit = 1;
	hit->p = vector_add(r.start, vector_scale(r.dir, hit->t));
	if (vector_dot(new->normal, r.dir) > 0.0)
		hit->n = vector_scale(new->normal, -1);
	else
		hit->n = new->normal;
	hit->m = new->material;
}

void	hit_cylinder(t_hit *hit, t_obj *new, t_ray r)
{
	double m;

	hit->hit = 1;
	hit->p = vector_add(r.start, vector_scale(r.dir, hit->t));
	m = vector_dot(r.dir, new->axis) * hit->t +
		vector_dot(vector_sub(r.start, new->pos), new->axis);
	hit->n = vector_normalize(vector_sub(vector_sub(hit->p, new->pos),
		vector_scale(new->axis, m)));
	if (vector_dot(hit->n, r.dir) > 0.0)
		hit->n = vector_scale(hit->n, -1);
	hit->m = new->material;
}

void	hit_cone(t_hit *hit, t_obj *new, t_ray r)
{
	double k;
	double m;

	hit->hit = 1;
	k = tan((new->angle * M_PI / 180.0) / 2);
	hit->p = vector_add(r.start, vector_scale(r.dir, hit->t));
	m = vector_dot(r.dir, new->axis) * hit->t +
		vector_dot(vector_sub(r.start, new->pos), new->axis);
	hit->n = vector_normalize(vector_sub(vector_sub(hit->p, new->pos),
		vector_scale(vector_scale(new->axis, m), (1 + k * k))));
	if (vector_dot(hit->n, r.dir) > 0.0)
		hit->n = vector_scale(hit->n, -1);
	hit->m = new->material;
}
