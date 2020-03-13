/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-oiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 00:01:00 by cel-oiri          #+#    #+#             */
/*   Updated: 2020/02/21 00:01:08 by cel-oiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector		ambient(t_hit *hit)
{
	return (vector_scale(hit->m.diffuse, 0.2));
}

t_vector		diffuse(t_shade_var var, t_hit *hit)
{
	double		lambert;
	t_vector	diff;

	lambert = vector_dot(var.r.dir, hit->n);
	diff = vector_scale(hit->m.diffuse, lambert);
	return (vector_add(vector_mult(var.light->color,
		vector_mult(diff, var.light->intensity)), var.color));
}

t_vector		specular(t_shade_var var, t_all *all, t_hit *hit)
{
	t_vector	view_dir;
	t_vector	light_reflect;
	double		spec_ref;

	view_dir = vector_normalize(vector_sub(all->cam.lookfrom, var.r.start));
	var.r.dir = vector_scale(var.r.dir, -1);
	light_reflect = vector_sub(var.r.dir, vector_scale(vector_scale(hit->n,
		vector_dot(var.r.dir, hit->n)), 2.0));
	spec_ref = vector_dot(light_reflect, view_dir);
	if (spec_ref > 0)
	{
		spec_ref = pow(spec_ref, 90);
		return (vector_add(vector_mult(var.light->color,
			vector_scale(var.light->intensity, spec_ref)), var.color));
	}
	return (var.color);
}

unsigned int	shade(t_all *all, t_hit *hit)
{
	t_shade_var var;
	t_vector	dist;

	var.light = all->lights;
	var.color = (t_vector){0.0, 0.0, 0.0};
	var.color = ambient(hit);
	while (var.light)
	{
		var.r.start = hit->p;
		dist = vector_sub(var.light->pos, hit->p);
		if (vector_dot(dist, hit->n) <= 0)
		{
			var.light = var.light->next;
			continue;
		}
		hit->t = sqrt(vector_dot(dist, dist));
		var.r.dir = vector_scale(dist, 1.0 / hit->t);
		if (!ray_secondary_intersection(all, &(var.r), hit))
		{
			var.color = diffuse(var, hit);
			var.color = specular(var, all, hit);
		}
		var.light = var.light->next;
	}
	return (rgb_color(var.color));
}
