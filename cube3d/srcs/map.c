/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 14:30:24 by lduhamel          #+#    #+#             */
/*   Updated: 2020/09/11 11:46:48 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		str_to_tab(t_maptab *tab)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	if (malloc_tab(tab) == -1)
		return (-1);
	while (j < tab->counter)
	{
		while (tab->map_str2[k] != '\n')
		{
			(tab->tab)[j][i] = tab->map_str2[k] - '0';
			k++;
			i++;
		}
		i = 0;
		k++;
		j++;
	}
	free_and_init(&tab->map_str2);
	return (1);
}

int		malloc_tab(t_maptab *tab)
{
	tab->i = 0;
	if (!(tab->tab = malloc(sizeof(int*) * (tab->counter))))
	{
		tab->error.ret = MALLOC_FAIL;
		return (-1);
	}
	while (tab->i < tab->counter)
	{
		if (!(tab->tab[tab->i++] = malloc(sizeof(int) * tab->len_max)))
		{
			tab->error.ret = MALLOC_FAIL;
			free_doubletab(tab->tab, tab->i);
			return (-1);
		}
	}
	return (1);
}

int		check_closing(t_maptab *tab, int height, int x, int y)
{
	if ((x < 0 || y < 0 || x == tab->len_max || y == height))
	{
		tab->error.ret = MAP_NOT_CLOSED;
		return (-1);
	}
	if (x >= 0 && y >= 0 && y < height && x < tab->len_max
			&& tab->tab[y][x] != 1
			&& tab->tab[y][x] != 2 && tab->sol[y][x] == 0)
	{
		tab->sol[y][x] = 1;
		if (check_closing(tab, height, x, y + 1) == -1)
			return (-1);
		if (check_closing(tab, height, x + 1, y) == -1)
			return (-1);
		if (check_closing(tab, height, x, y - 1) == -1)
			return (-1);
		if (check_closing(tab, height, x - 1, y) == -1)
			return (-1);
		if (check_closing(tab, height, x - 1, y) == -1)
			return (-1);
		return (1);
	}
	return (1);
}

int		check_diagonals(t_maptab *tab, int height, int x, int y)
{
	if (x == 0)
		x++;
	if (x == tab->len_max - 1)
	{
		y++;
		x = 1;
	}
	if (y == height - 1)
		return (1);
	if ((tab->tab[y][x] == 1 && tab->tab[y + 1][x - 1] == 1
		&& tab->tab[y][x - 1] == 0 && tab->tab[y + 1][x] == 0)
		|| (tab->tab[y][x] == 1 && tab->tab[y + 1][x + 1] == 1
		&& tab->tab[y][x + 1] == 0 && tab->tab[y + 1][x] == 0))
	{
		tab->error.ret = DIAGONAL_WALL;
		return (-1);
	}
	if (y < height - 1)
	{
		if (check_diagonals(tab, height, x + 1, y) == -1)
			return (-1);
		return (1);
	}
	return (1);
}
