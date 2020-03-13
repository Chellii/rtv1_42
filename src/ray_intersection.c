/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-oiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 23:44:55 by cel-oiri          #+#    #+#             */
/*   Updated: 2020/02/26 23:44:56 by cel-oiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_ray	get_ray(double u, double v, t_camera *c)
{
	t_ray		r;
	t_vector	dir;

	c->origin = c->lookfrom;
	c->k = vector_normalize(vector_sub(c->lookfrom, c->lookat));
	c->i = vector_normalize(vector_cross(c->lookup, c->k));
	c->j = vector_cross(c->k, c->i);
	c->w = vector_sub(c->origin, vector_add(vector_add(vector_scale(c->i,
						c->half_width),
					vector_scale(c->j, c->half_height)), c->k));
	c->horizontal = vector_scale(c->i, 2.0 * c->half_width);
	c->vertical = vector_scale(c->j, 2.0 * c->half_height);
	dir = vector_add(vector_add(vector_scale(c->horizontal, u),
				vector_scale(c->vertical, v)), c->w);
	r.start = c->origin;
	dir = vector_sub(dir, r.start);
	r.dir = vector_normalize(dir);
	return (r);
}

t_hit	ray_primary_intersection(t_all *all, t_ray *ray)
{
	t_obj *new;
	t_hit hit;
	t_ray r;

	r = *ray;
	new = all->obj;
	hit.hit = 0;
	hit.t = INFINITY;
	while (new)
	{
		if (new->type == SPHERE && intersect_ray_sphere(&r, new, &hit.t))
			hit_sphere(&hit, new, r);
		else if (new->type == PLANE && intersect_ray_plan(&r, new, &hit.t))
			hit_plan(&hit, new, r);
		else if (new->type == CYLINDER &&
			intersect_ray_cylinder(&r, new, &hit.t))
			hit_cylinder(&hit, new, r);
		else if (new->type == CONE && intersect_ray_cone(&r, new, &hit.t))
			hit_cone(&hit, new, r);
		new = new->next;
	}
	return (hit);
}

int		ray_secondary_intersection(t_all *all, t_ray *ray, t_hit *hit)
{
	t_obj	*new;
	t_ray	r;

	r = *ray;
	new = all->obj;
	while (new)
	{
		r.start = vector_add(hit->p, vector_scale(hit->n, 0.0001));
		if (new->type == SPHERE && intersect_ray_sphere(&r, new, &(hit->t)))
			return (1);
		else if (new->type == PLANE && intersect_ray_plan(&r, new, &(hit->t)))
			return (1);
		else if (new->type == CYLINDER && intersect_ray_cylinder(&r, new,
			&(hit->t)))
			return (1);
		else if (new->type == CONE && intersect_ray_cone(&r, new, &(hit->t)))
			return (1);
		new = new->next;
	}
	return (0);
}
