/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-oiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 18:48:45 by cel-oiri          #+#    #+#             */
/*   Updated: 2020/02/20 18:48:46 by cel-oiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		insert_parsl(t_list_pars **lt, char *str)
{
	t_list_pars *l;
	t_list_pars *l2;

	if (!(l = (t_list_pars*)malloc(sizeof(t_list_pars))))
		exit(1);
	l->str = str;
	l->next = NULL;
	l2 = *lt;
	if (l2 == NULL)
	{
		*lt = l;
	}
	else
	{
		while (l2->next != NULL)
			l2 = l2->next;
		l2->next = l;
	}
}

void		insert_all(t_all *all, t_list_pars *l)
{
	while ((l != NULL) && (ft_strcmp(l->str, "camera") != 0))
		l = l->next;
	if ((l != NULL) && (ft_strcmp(l->str, "camera") == 0))
		insert_cam(&l, all);
	while ((l != NULL) && (ft_strcmp(l->str, "light") != 0))
	{
		if (ft_strcmp(l->str, "sphere") == 0)
			insert_sph(&l, all);
		if (ft_strcmp(l->str, "plane") == 0)
			insert_plane(&l, all);
		if (ft_strcmp(l->str, "cone") == 0)
			insert_cone(&l, all);
		if (ft_strcmp(l->str, "cylinder") == 0)
			insert_cylinder(&l, all);
		l = l->next;
	}
	while ((l != NULL) && (ft_strcmp(l->str, "light") == 0))
	{
		insert_light(&l, all);
		l = l->next;
	}
}

t_list_pars	*insert_list(char *namefile)
{
	int			fd;
	t_list_pars	*lt;
	char		*line;

	lt = NULL;
	line = NULL;
	if ((fd = open(namefile, O_RDONLY)) == -1)
	{
		ft_putstr("No file : ");
		ft_putendl(namefile);
		close(fd);
		exit(1);
	}
	while (get_next_line(fd, &line, 0) == 1)
	{
		if (ft_strcmp(line, "") != 0)
			insert_parsl(&lt, line);
		else
			free(line);
	}
	close(fd);
	get_next_line(fd, &line, 1);
	return (lt);
}

t_all		*ft_all(char *namefile)
{
	t_all		*all;
	t_list_pars	*lt;
	t_list_pars *l;

	lt = insert_list(namefile);
	l = lt;
	if (!(verif_format_file(l)))
	{
		free_list(lt);
		exit(1);
	}
	if (!(all = (t_all*)malloc(sizeof(t_all))))
		exit(1);
	all->obj = NULL;
	all->lights = NULL;
	insert_all(all, lt);
	free_list(lt);
	return (all);
}
