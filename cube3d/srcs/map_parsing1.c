/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 12:02:43 by lduhamel          #+#    #+#             */
/*   Updated: 2020/09/12 12:02:55 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		len_row(t_maptab *tab)
{
	int i;
	int len1;
	int len2;
	int len_max;

	i = 0;
	len1 = 0;
	len2 = 0;
	while (tab->map_str1[i] != '\0')
	{
		while (tab->map_str1[i] != '\n')
		{
			i++;
			len1++;
		}
		len_max = (len1 > len2 ? len1 : len2);
		len2 = len_max;
		len1 = 0;
		i += 1;
	}
	return (len_max);
}

int		fill_shorter_lines(t_maptab *tab)
{
	int i;
	int j;
	int limit;

	i = 0;
	j = 0;
	tab->len_max = len_row(tab);
	limit = tab->len_max;
	if (fill_shorter_lines2(tab, i, j, limit) == -1)
		return (-1);
	free_and_init(&tab->map_str1);
	return (1);
}

int		fill_shorter_lines2(t_maptab *tab, int i, int j, int limit)
{
	if (!(tab->map_str2 = (char*)malloc(sizeof(char) *
		(((tab->len_max + 1) * tab->counter) + 1))))
	{
		tab->error.ret = MALLOC_FAIL;
		return (-1);
	}
	tab->counter = 0;
	while (tab->map_str1[i] != '\0')
	{
		while (tab->map_str1[i] != '\0' && tab->map_str1[i] != '\n')
			tab->map_str2[j++] = tab->map_str1[i++];
		while (j < limit)
		{
			tab->map_str2[j] = '0';
			j++;
		}
		tab->map_str2[j++] = tab->map_str1[i++];
		tab->counter++;
		limit = (limit + tab->len_max + 1);
	}
	tab->map_str2[j] = '\0';
	return (1);
}

int		player_position(t_maptab *tab, t_info *info, int width, int height)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			player_angle(tab, info, i, j);
			if (tab->tab[i][j] == 3 || tab->tab[i][j] == 4
				|| tab->tab[i][j] == 5 || tab->tab[i][j] == 6)
			{
				tab->x = j;
				tab->y = i;
				tab->tab[i][j] = 0;
			}
			j++;
		}
		i++;
	}
	tab->i = 0;
	tab->j = 0;
	return (1);
}
