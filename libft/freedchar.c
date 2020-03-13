/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedchar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-oiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 13:27:23 by cel-oiri          #+#    #+#             */
/*   Updated: 2020/02/21 00:59:51 by cel-oiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	freedchar(char **tab)
{
	int		i;
	char	**tab_tracker;

	i = 0;
	tab_tracker = tab;
	while (tab_tracker[i] != NULL)
	{
		free(tab_tracker[i]);
		i++;
	}
	free(tab_tracker);
}
