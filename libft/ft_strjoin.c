/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-oiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 14:23:03 by cel-oiri          #+#    #+#             */
/*   Updated: 2020/02/12 22:24:48 by cel-oiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;

	if (s1 && s2)
	{
		if (!(str = (char*)malloc(sizeof(char)
						* (ft_strlen(s1) + ft_strlen(s2) + 1))))
			return (0);
		str = ft_strcpy(str, s1);
		str = ft_strcat(str, s2);
		return (str);
	}
	return (NULL);
}
