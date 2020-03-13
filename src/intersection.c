/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-oiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 23:45:19 by cel-oiri          #+#    #+#             */
/*   Updated: 2020/03/09 21:56:09 by cel-oiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

int		intersect_ray_sphere(t_ray *r, t_obj *s, double *t)
{
	t_intersect_var var;

	var.a = vector_dot(r->dir, r->dir);
	var.dist = vector_sub(r->start, s->pos);
	var.b = 2 * vector_dot(r->dir, var.dist);
	var.c = vector_dot(var.dist, var.dist) - (s->radius * s->radius);
	var.delta = var.b * var.b - 4 * var.a * var.c;
	if (var.delta < 0)
		return (0);
	var.sqrdelta = sqrtf(var.delta);
	var.t1 = (-var.b + var.sqrdelta) / (2 * var.a);
	var.t0 = (-var.b - var.sqrdelta) / (2 * var.a);
	var.min = ft_min_ray(var.t0, var.t1, t);
	return (var.min);
}

int		intersect_ray_plan(t_ray *r, t_obj *p, double *t)
{
	double		m;
	double		t0;
	t_vector	dist;

	m = vector_dot(r->dir, p->normal);
	if (m != 0)
	{
		dist = vector_sub(r->start, p->pos);
		t0 = (-vector_dot(dist, p->normal)) / m;
		if (t0 > MIN_DIS && t0 < *t)
		{
			*t = t0;
			return (1);
		}
	}
	return (0);
}

int		intersect_ray_cylinder(t_ray *r, t_obj *cyl, double *t)
{
	t_intersect_var var;

	var.dist = vector_sub(r->start, cyl->pos);
	var.a = vector_dot(r->dir, r->dir) - (vector_dot(r->dir, cyl->axis) *
			vector_dot(r->dir, cyl->axis));
	var.b = 2 * (vector_dot(r->dir, var.dist) - vector_dot(r->dir, cyl->axis) *
			vector_dot(var.dist, cyl->axis));
	var.c = vector_dot(var.dist, var.dist) - (vector_dot(var.dist, cyl->axis) *
			vector_dot(var.dist, cyl->axis)) - cyl->radius * cyl->radius;
	var.delta = var.b * var.b - 4 * var.a * var.c;
	var.sqrdelta = sqrt(var.delta);
	if (var.delta < 0.0)
		return (0);
	var.t0 = (-var.b - var.sqrdelta) / (2 * var.a);
	var.t1 = (-var.b + var.sqrdelta) / (2 * var.a);
	var.min = ft_min_ray(var.t0, var.t1, t);
	return (var.min);
}

int		intersect_ray_cone(t_ray *r, t_obj *cone, double *t)
{
	t_intersect_var var;

	var.dist = vector_sub(r->start, cone->pos);
	var.k = tan((cone->angle * M_PI / 180.0) / 2);
	var.a = vector_dot(r->dir, r->dir) -
		(1 + (var.k * var.k)) * (vector_dot(r->dir, cone->axis) *
				vector_dot(r->dir, cone->axis));
	var.b = 2 * (vector_dot(r->dir, var.dist) - (1 + var.k * var.k) *
			(vector_dot(r->dir, cone->axis)
			* vector_dot(var.dist, cone->axis)));
	var.c = vector_dot(var.dist, var.dist) - ((1 + var.k * var.k) *
			(vector_dot(var.dist, cone->axis) * vector_dot(var.dist,
			cone->axis)));
	var.delta = var.b * var.b - 4 * var.a * var.c;
	var.sqrdelta = sqrt(var.delta);
	if (var.delta < 0.0)
		return (0);
	var.t0 = (-var.b - var.sqrdelta) / (2 * var.a);
	var.t1 = (-var.b + var.sqrdelta) / (2 * var.a);
	var.min = ft_min_ray(var.t0, var.t1, t);
	return (var.min);
}
