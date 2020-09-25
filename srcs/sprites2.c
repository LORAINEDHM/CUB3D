/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 13:12:47 by lduhamel          #+#    #+#             */
/*   Updated: 2020/09/21 21:37:39 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

double		spriteheight(t_info *info, double distance)
{
	double corrected_distance;
	double height;

	corrected_distance = fishbowlsprite(info, distance);
	height = projected_slice_height(info, corrected_distance);
	return (height);
}

double		fishbowlsprite(t_info *info, double distorted_distance)
{
	double corrected_distance;

	if (info->angle < info->barrel.spriteangle)
		corrected_distance = distorted_distance
		* cos(ft_deg2rad(info->barrel.spriteangle - info->angle));
	else
		corrected_distance = distorted_distance
		* cos(ft_deg2rad(info->angle - info->barrel.spriteangle));
	return (corrected_distance);
}

void		seekdrawstart(t_info *info, int i)
{
	info->barrel.startdrawx = info->barrel.x[i] + info->barrel.plandir.x;
	info->barrel.startdrawy = info->barrel.y[i] + info->barrel.plandir.y;
}

int			findray(t_info *info, int i, double x, double y)
{
	double	dist;
	double	dist2;
	int		whichray;

	info->barrel.point.x = x;
	info->barrel.point.y = y;
	whichray = 0;
	while (whichray < info->screenwidth - 1)
	{
		info->barrel.droite.a = info->barrel.a[whichray];
		info->barrel.droite.b = -1;
		info->barrel.droite.c = info->barrel.c[whichray];
		info->barrel.droite2.a = info->barrel.a[whichray + 1];
		info->barrel.droite2.b = -1;
		info->barrel.droite2.c = info->barrel.c[whichray + 1];
		dist = ft_distpointdroite(info->barrel.point, info->barrel.droite);
		dist2 = ft_distpointdroite(info->barrel.point, info->barrel.droite2);
		if (dist < dist2)
			break ;
		whichray++;
	}
	if (whichray == info->screenwidth - 1)
		return (whichray);
	return (whichray - 1);
}

void		print_sprite(t_info *info, int i)
{
	if (info->barrel.startray < 0)
	{
		info->barrel.startdrawx = info->barrel.x[i] - info->barrel.plandir.x;
		info->barrel.startdrawy = info->barrel.y[i] - info->barrel.plandir.y;
		info->barrel.endray = findray(info, i,
				info->barrel.startdrawx, info->barrel.startdrawy);
		if (info->barrel.endray == info->screenwidth - 1)
			print_sprite_middle(info, i);
		else
			print_sprite_right(info, i, info->barrel.endray, 64);
	}
	else
		print_sprite_left(info, i, info->barrel.startray, 0);
}
