/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_format_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-oiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 16:02:10 by cel-oiri          #+#    #+#             */
/*   Updated: 2020/02/20 19:11:28 by cel-oiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		verif_obj(t_list_pars **l)
{
	t_list_pars	*l2;
	int			v;

	l2 = (*l);
	while ((l2 != NULL) && (verif_name_obj(l2->str)))
	{
		v = 1;
		l2 = verif_sphere(l2, &v);
		if (!(wrong_format(v)))
			return (0);
		v = 1;
		l2 = verif_plane(l2, &v);
		if (!(wrong_format(v)))
			return (0);
		v = 1;
		l2 = verif_cone_cyl(l2, &v);
		if (!(wrong_format(v)))
			return (0);
	}
	(*l) = l2;
	return (1);
}

int		verif_light(t_list_pars **l)
{
	t_list_pars	*l2;
	int			i;

	l2 = (*l);
	while ((l2 != NULL) && (ft_strcmp(l2->str, "light") == 0))
	{
		i = 0;
		l2 = l2->next;
		while ((l2 != NULL) && (i < 3))
		{
			if ((length_line_nbr(l2->str)) != 3)
				return (0);
			l2 = l2->next;
			i++;
		}
		if ((l2 == NULL) && (i != 3))
			return (0);
	}
	(*l) = l2;
	return (1);
}

int		verif_object_1(t_list_pars **l)
{
	if (((*l) != NULL) && (verif_name_obj((*l)->str)))
	{
		if (!(verif_obj(l)))
			return (0);
		if (((*l) != NULL) && (ft_strcmp((*l)->str, "light") == 0))
		{
			if (!(verif_light(l)))
			{
				ft_putendl("Wrong format file.");
				return (0);
			}
		}
		else
		{
			ft_putendl("Wrong format file.");
			return (0);
		}
	}
	else
	{
		ft_putendl("Wrong format file.");
		return (0);
	}
	return (1);
}

int		verif_format_file_2(t_list_pars **l)
{
	if (!(verif_camera(l)))
		return (0);
	if (!(verif_object_1(l)))
		return (0);
	return (1);
}

int		verif_format_file(t_list_pars *lt)
{
	t_list_pars **l;

	if (!(l = (t_list_pars**)malloc(sizeof(t_list_pars))))
		exit(1);
	*l = lt;
	while (((*l) != NULL) && ((ft_strcmp((*l)->str, "camera") != 0)))
		*l = (*l)->next;
	if (((*l) != NULL) && (ft_strcmp((*l)->str, "camera") == 0))
	{
		if (!(verif_format_file_2(l)))
		{
			free(l);
			return (0);
		}
	}
	else
	{
		ft_putendl("Wrong format file.");
		free(l);
		return (0);
	}
	free(l);
	return (1);
}
