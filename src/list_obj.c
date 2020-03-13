/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-oiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 20:11:00 by cel-oiri          #+#    #+#             */
/*   Updated: 2020/02/20 00:25:42 by cel-oiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_obj	*ft_obj_new(t_obj o)
{
	t_obj	*new;

	if (!(new = (t_obj*)malloc(sizeof(t_obj))))
		exit(EXIT_FAILURE);
	new->type = o.type;
	new->radius = o.radius;
	new->angle = o.angle;
	new->normal = o.normal;
	new->pos = o.pos;
	new->axis = o.axis;
	if (o.trans.x != 0 || o.trans.y != 0 || o.trans.z != 0)
		translation(&new->pos, o.trans);
	if (!(o.rot.x != 0 && o.rot.y != 0 && o.rot.z != 0))
		rotation(&new->axis, o.rot);
	new->material = o.material;
	new->next = NULL;
	return (new);
}

void	ft_add_obj_back(t_obj **list, t_obj *new)
{
	t_obj	*curr;

	if (!list || !new)
		return ;
	if (!*list)
	{
		*list = new;
		return ;
	}
	else
	{
		curr = *list;
		while (curr->next)
			curr = curr->next;
		if (curr)
			curr->next = new;
	}
}
