/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 23:15:16 by lduhamel          #+#    #+#             */
/*   Updated: 2020/09/22 11:33:17 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		coordinatesofbarrel(t_info *info)
{
	int i;
	int j;
	int n;

	i = 0;
	j = 0;
	n = 0;
	while (i < info->mapheight)
	{
		j = 0;
		while (j < info->mapwidth)
		{
			if (info->worldmap[i][j] == 2)
			{
				info->barrel.x[n] = j * 64 + 32;
				info->barrel.y[n] = (info->mapheight - 1 - i) * 64 + 32;
				n++;
			}
			j++;
		}
		i++;
	}
}

void		handlesprites(t_info *info)
{
	int i;

	i = 0;
	distance_2_sprite(info);
	ft_sort_sprites(info);
	while (i < info->nbsprite)
	{
		initialise(info, i);
		if (fabs(info->barrel.spriteangle - info->angle) < 90
			|| fabs(info->barrel.spriteangle - info->angle) > 270)
		{
			seekdrawstart(info, i);
			info->barrel.middleray = findray(info, i,
					info->barrel.x[i], info->barrel.y[i]);
			info->barrel.startray = findray(info, i,
					info->barrel.startdrawx, info->barrel.startdrawy);
			print_sprite(info, i);
		}
		i++;
	}
}

void		distance_2_sprite(t_info *info)
{
	int i;

	i = 0;
	while (i < info->nbsprite)
	{
		info->barrel.dist[i] = sqrt(pow(info->barrel.x[i] - info->a.x, 2)
			+ pow(info->barrel.y[i] - info->a.y, 2));
		i++;
	}
}

void		ft_sort_sprites(t_info *info)
{
	int		count;
	int		i;
	double	tmp[3];

	count = 0;
	while (count < info->nbsprite)
	{
		i = -1;
		while (++i < (info->nbsprite) - 1)
		{
			if (info->barrel.dist[i] < info->barrel.dist[i + 1])
			{
				tmp[0] = info->barrel.dist[i];
				tmp[1] = info->barrel.x[i];
				tmp[2] = info->barrel.y[i];
				info->barrel.dist[i] = info->barrel.dist[i + 1];
				info->barrel.x[i] = info->barrel.x[i + 1];
				info->barrel.y[i] = info->barrel.y[i + 1];
				info->barrel.dist[i + 1] = tmp[0];
				info->barrel.x[i + 1] = tmp[1];
				info->barrel.y[i + 1] = tmp[2];
			}
		}
		count++;
	}
}

void		initialise(t_info *info, int i)
{
	t_p spritecoordinates;

	spritecoordinates.x = info->barrel.x[i];
	spritecoordinates.y = info->barrel.y[i];
	ray(&info->barrel.spriteray, info->a, spritecoordinates);
	info->barrel.spriteangle = ft_rad2deg(atan(fabs(info->barrel.spriteray.m)));
	if (info->barrel.spriteray.m == 0)
		info->barrel.spriteangle = (info->barrel.x[i] > info->a.x ? 0 : 180);
	else if (info->barrel.spriteray.m > 0)
		info->barrel.spriteangle += (info->barrel.y[i] < info->a.y ? 180 : 0);
	else
	{
		info->barrel.spriteangle = 180 - info->barrel.spriteangle;
		info->barrel.spriteangle += (info->barrel.y[i] < info->a.y ? 180 : 0);
	}
	info->barrel.plandir.x = cos(ft_deg2rad(info->angle + 90)) * BLOCKSIZE / 2;
	info->barrel.plandir.y = sin(ft_deg2rad(info->angle + 90)) * BLOCKSIZE / 2;
	info->barrel.height = spriteheight(info, info->barrel.dist[i]);
	info->barrel.ystart = (info->screenheight - info->barrel.height) / 2;
}
