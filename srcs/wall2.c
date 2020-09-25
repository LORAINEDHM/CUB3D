/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 13:52:54 by lduhamel          #+#    #+#             */
/*   Updated: 2020/09/21 21:37:50 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

double	cub_redflag(t_info *info)
{
	if (info->redflag[0] == 1)
	{
		info->side = 1;
		info->wall[0] = info->test_axis[1].x;
		info->wall[1] = info->test_axis[1].y;
		return (distance_2_points(info->a, info->test_axis[1]));
	}
	else
	{
		info->side = 0;
		info->wall[0] = info->test_axis[0].x;
		info->wall[1] = info->test_axis[0].y;
		return (distance_2_points(info->a, info->test_axis[0]));
	}
}

int		hit_map(t_info *info, int n)
{
	if (info->a.x < info->p_of_plan.x)
		info->map[0].x = bloc_to_map(info->test_axis[n].x, BLOCKSIZE);
	else
		info->map[0].x = bloc_to_map(info->test_axis[n].x, BLOCKSIZE) - 1;
	info->map[0].y = bloc_to_map(info->test_axis[n].y, BLOCKSIZE);
	info->map[1].x = bloc_to_map(info->test_axis[n].x, BLOCKSIZE);
	if (info->a.y < info->p_of_plan.y)
		info->map[1].y = bloc_to_map(info->test_axis[n].y, BLOCKSIZE);
	else
		info->map[1].y = bloc_to_map(info->test_axis[n].y, BLOCKSIZE) - 1;
	if (info->map[n].x < 0
	|| !(info->map[n].y >= 0 && info->map[n].y < info->mapheight))
		return (1);
	if (info->worldmap[(info->mapheight - 1)
	- info->map[n].y][info->map[n].x] == 1)
		return (1);
	return (0);
}

/*
**function that handles everything related to the walls once we have
**the correct distance to a wall
*/

double	walls(t_info *info, double distance, int whichray)
{
	double corrected_distance;
	double slice_height;

	corrected_distance = fishbowl(info, distance, whichray);
	slice_height = projected_slice_height(info, corrected_distance);
	return (slice_height);
}

/*
**https://www.permadi.com/tutorial/raycast/rayc8.html
**pour afficher un mur droit quand on est face a un mur
*/

double	fishbowl(t_info *info, double distorted_distance, int whichray)
{
	double angle_offset;
	double corrected_distance;

	angle_offset = (double)POV / info->screenwidth;
	if (whichray < (int)(info->screenwidth / 2))
		corrected_distance = distorted_distance
			* cos(ft_deg2rad(((double)POV / 2) - (whichray * angle_offset)));
	else
		corrected_distance = distorted_distance
			* cos(ft_deg2rad(((whichray - (info->screenwidth / 2))
			* angle_offset)));
	return (corrected_distance);
}

/*
**https://www.permadi.com/tutorial/raycast/rayc9.html
**adapter la taille du mur par rapport a
**la distance au plan et non la réelle distance
*/

double	projected_slice_height(t_info *info, double distance)
{
	double projected_slice_height;

	projected_slice_height = (BLOCKSIZE / distance) * info->ad;
	return (projected_slice_height);
}
