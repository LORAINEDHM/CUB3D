/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 18:14:38 by lduhamel          #+#    #+#             */
/*   Updated: 2020/09/21 21:37:14 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	init_parsing(t_element *elem, t_maptab *tab, t_info *info)
{
	info->sp_texture = NULL;
	info->no_texture = NULL;
	info->so_texture = NULL;
	info->we_texture = NULL;
	info->ea_texture = NULL;
	elem->bitflag = 0;
	elem->counter = 0;
	elem->nb_flag = 0;
	elem->ret = 1;
	info->nbsprite = 0;
	tab->ret = 1;
	tab->counter = 0;
	tab->letter = 0;
	tab->i = 0;
	tab->error.ret = 0;
	tab->line = NULL;
	tab->map_str1 = NULL;
	tab->map_str2 = NULL;
	tab->tab = NULL;
	tab->sol = NULL;
}

int		ft_init(t_info *info, t_maptab *tab)
{
	info->mlx_ptr = NULL;
	info->win_ptr = NULL;
	info->img = NULL;
	info->mapwidth = tab->len_max;
	info->mapheight = tab->counter;
	info->a.x = tab->x * 64 + 32;
	info->a.y = (info->mapheight - 1 - tab->y) * 64 + 32;
	info->bad = (double)POV / 2;
	info->bd = info->screenwidth / 2;
	info->ad = toa(info->bad, info->bd);
	info->dir.x = cos(ft_deg2rad(info->angle)) * info->ad;
	info->dir.y = sin(ft_deg2rad(info->angle)) * info->ad;
	info->plan.x = cos(ft_deg2rad(info->angle + 90)) * info->bd;
	info->plan.y = sin(ft_deg2rad(info->angle + 90)) * info->bd;
	info->b.x = info->a.x + info->dir.x + info->plan.x;
	info->b.y = info->a.y + info->dir.y + info->plan.y;
	info->c.x = info->a.x + info->dir.x - info->plan.x;
	info->c.y = info->a.y + info->dir.y - info->plan.y;
	if (ft_init2(info, tab) == -1)
		return (-1);
	return (1);
}

int		ft_init2(t_info *info, t_maptab *tab)
{
	info->next_axis_x = (int)info->a.x
	+ (int)BLOCKSIZE - ((int)info->a.x % (int)BLOCKSIZE);
	info->next_axis_y = (int)info->a.y
	+ (int)BLOCKSIZE - ((int)info->a.y % (int)BLOCKSIZE);
	info->move.up = 0;
	info->move.down = 0;
	info->move.right = 0;
	info->move.left = 0;
	info->side = 0;
	info->tex_x = 0;
	info->error = SUCCESS;
	if (barrel_xytab(info, tab) == -1 || saveintabs(info, tab) == -1)
		return (-1);
	coordinatesofbarrel(info);
	return (1);
}

int		barrel_xytab(t_info *info, t_maptab *tab)
{
	if ((!(info->barrel.x = malloc(sizeof(double) * (info->nbsprite))))
		|| (!(info->barrel.y = malloc(sizeof(double) * (info->nbsprite)))))
	{
		error_msg(info, tab, &tab->error, 3);
		return (-1);
	}
	return (1);
}

int		saveintabs(t_info *info, t_maptab *tab)
{
	if ((!(info->barrel.dist = malloc(sizeof(double) * (info->nbsprite))))
	|| (!(info->barrel.walldist = malloc(sizeof(double) * (info->screenwidth))))
	|| (!(info->barrel.a = malloc(sizeof(double) * (info->screenwidth))))
	|| (!(info->barrel.c = malloc(sizeof(double) * (info->screenwidth)))))
	{
		error_msg(info, tab, &tab->error, 3);
		return (-1);
	}
	return (1);
}
