/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-oiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 20:11:00 by cel-oiri          #+#    #+#             */
/*   Updated: 2020/02/20 00:22:16 by cel-oiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		insert_light(t_list_pars **lt, t_all *all)
{
	t_vector	pos;
	t_vector	color;
	t_vector	intensity;
	char		**tab;
	t_list_pars	*l;

	l = (*lt)->next;
	tab = ft_strsplit(l->str, ' ');
	pos = (t_vector){ft_atof(tab[0]), ft_atof(tab[1]), ft_atof(tab[2])};
	freedchar(tab);
	l = l->next;
	tab = ft_strsplit(l->str, ' ');
	color = (t_vector){ft_atof(tab[0]) / 255, ft_atof(tab[1]) / 255,
		ft_atof(tab[2]) / 255};
	freedchar(tab);
	l = l->next;
	tab = ft_strsplit(l->str, ' ');
	intensity = (t_vector){ft_atof(tab[0]), ft_atof(tab[1]), ft_atof(tab[2])};
	freedchar(tab);
	ft_add_light_back(&(all->lights), ft_light_new(pos, color, intensity));
	(*lt) = l;
}

t_light		*ft_light_new(t_vector pos, t_vector color, t_vector intensity)
{
	t_light	*new;

	if (!(new = malloc(sizeof(t_light))))
		exit(1);
	if (!(new))
	{
		ft_putendl("malloc error");
		exit(EXIT_FAILURE);
	}
	new->pos = pos;
	new->intensity = intensity;
	new->color = color;
	new->next = NULL;
	return (new);
}

void		ft_add_light_back(t_light **list, t_light *new)
{
	t_light	*curr;

	if (!list || !new)
		return ;
	if (!*list)
	{
		*list = new;
		return ;
	}
	curr = *list;
	while (curr->next)
		curr = curr->next;
	if (curr)
		curr->next = new;
}
