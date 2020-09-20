/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 12:03:38 by lduhamel          #+#    #+#             */
/*   Updated: 2020/09/12 12:03:44 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	player_angle(t_maptab *tab, t_info *info, int i, int j)
{
	if (tab->tab[i][j] == 3)
		info->angle = 90;
	if (tab->tab[i][j] == 4)
		info->angle = 180;
	if (tab->tab[i][j] == 5)
		info->angle = 270;
	if (tab->tab[i][j] == 6)
		info->angle = 0;
}

int		mallocandinit_tab_sol(t_maptab *tab)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!(tab->sol = malloc(sizeof(int*) * (tab->counter))))
	{
		tab->error.ret = MALLOC_FAIL;
		return (-1);
	}
	if (init_tab_sol(tab, i, j) == -1)
		return (-1);
	return (1);
}

int		init_tab_sol(t_maptab *tab, int i, int j)
{
	while (i < tab->counter)
	{
		if (!(tab->sol[i++] = malloc(sizeof(int) * tab->len_max)))
		{
			tab->error.ret = MALLOC_FAIL;
			free_doubletab(tab->sol, i);
			return (-1);
		}
	}
	i = 0;
	while (j < tab->counter)
	{
		while (i < tab->len_max)
		{
			tab->sol[j][i] = 0;
			i++;
		}
		i = 0;
		j++;
	}
	return (1);
}

int		checking_map(t_maptab *tab, t_info *info)
{
	if (tab->letter == 0)
	{
		tab->error.ret = WRONG_NB_OF_LETTER;
		error_msg(info, tab, &tab->error, 1);
		return (-1);
	}
	if (fill_shorter_lines(tab) == -1
		|| str_to_tab(tab) == -1
		|| player_position(tab, info, tab->len_max, tab->counter) == -1
		|| check_diagonals(tab, tab->counter, tab->i, tab->j) == -1
		|| mallocandinit_tab_sol(tab) == -1
		|| check_closing(tab, tab->counter, tab->x, tab->y) == -1)
	{
		error_msg(info, tab, &tab->error, 2);
		return (-1);
	}
	free_doubletab(tab->sol, tab->counter - 1);
	return (1);
}
