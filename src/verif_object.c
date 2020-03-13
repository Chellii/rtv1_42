/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-oiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 19:50:41 by cel-oiri          #+#    #+#             */
/*   Updated: 2020/02/20 19:50:41 by cel-oiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				length_line_nbr(char *str)
{
	char	**tab;
	int		i;

	i = 0;
	tab = ft_strsplit(str, ' ');
	while (tab[i] != NULL)
	{
		if ((ft_strncmp(tab[i], "0.0", 3) != 0) &&
			(ft_atof(tab[i]) == 0.000000))
		{
			freedchar(tab);
			return (0);
		}
		i++;
	}
	freedchar(tab);
	return (i);
}

int				verif_name_obj(char *str)
{
	if ((ft_strcmp(str, "sphere") == 0) || (ft_strcmp(str, "cone") == 0) ||
		(ft_strcmp(str, "plane") == 0) || (ft_strcmp(str, "cylinder") == 0))
		return (1);
	return (0);
}

t_list_pars		*verif_sphere(t_list_pars *l2, int *v)
{
	int i;
	int vec;
	int line;

	if ((l2 != NULL) && (ft_strcmp(l2->str, "sphere") == 0))
	{
		i = 0;
		vec = 0;
		line = 0;
		l2 = l2->next;
		while ((l2 != NULL) && (i < 5))
		{
			if ((length_line_nbr(l2->str)) == 3)
				vec++;
			else if ((i == 1) && (length_line_nbr(l2->str)) == 1)
				line++;
			else
				*v = 0;
			l2 = l2->next;
			i++;
		}
		if ((line != 1) || (vec != 4))
			*v = 0;
	}
	return (l2);
}

t_list_pars		*verif_plane(t_list_pars *l2, int *v)
{
	int i;

	if ((l2 != NULL) && (ft_strcmp(l2->str, "plane") == 0))
	{
		i = 0;
		l2 = l2->next;
		while ((l2 != NULL) && (i < 5))
		{
			if ((length_line_nbr(l2->str)) != 3)
				*v = 0;
			l2 = l2->next;
			i++;
		}
	}
	return (l2);
}

t_list_pars		*verif_cone_cyl(t_list_pars *l2, int *v)
{
	int i;
	int vec;
	int line;

	if ((l2 != NULL) && ((ft_strcmp(l2->str, "cone") == 0) ||
		(ft_strcmp(l2->str, "cylinder") == 0)))
	{
		l2 = l2->next;
		i = 0;
		vec = 0;
		line = 0;
		while ((l2 != NULL) && (i++ < 6))
		{
			if ((length_line_nbr(l2->str)) == 3)
				vec++;
			else if ((i == 3) && (length_line_nbr(l2->str) == 1))
				line++;
			else
				*v = 0;
			l2 = l2->next;
		}
		if ((line != 1) || (vec != 5))
			*v = 0;
	}
	return (l2);
}
