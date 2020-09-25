/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 23:16:03 by lduhamel          #+#    #+#             */
/*   Updated: 2020/09/22 11:33:49 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	p_on_plan(t_info *info, double whichray)
{
	info->p_of_plan.x = info->b.x
		- (whichray * (info->b.x - info->c.x) / info->screenwidth);
	info->p_of_plan.y = info->b.y
		- (whichray * (info->b.y - info->c.y) / info->screenwidth);
}

void	test_x_axis(t_info *info)
{
	int hit;
	int n;

	n = 0;
	hit = 0;
	info->redflag[0] = 0;
	info->test_axis[n].x = (info->a.x < info->p_of_plan.x)
		? info->next_axis_x : info->next_axis_x - BLOCKSIZE;
	while (hit == 0)
	{
		find_y(&info->test_axis[n], info->ray.m, info->ray.n);
		if (map_bounderies(info, n) == 1)
			break ;
		if ((hit = hit_map(info, n) == 1))
			break ;
		info->test_axis[n].x += (info->a.x < info->p_of_plan.x)
			? BLOCKSIZE : -BLOCKSIZE;
	}
}

void	test_y_axis(t_info *info)
{
	int hit;
	int n;

	n = 1;
	hit = 0;
	info->redflag[1] = 0;
	info->test_axis[n].y = (info->a.y < info->p_of_plan.y)
		? info->next_axis_y : info->next_axis_y - BLOCKSIZE;
	while (hit == 0)
	{
		find_x(&info->test_axis[n], info->ray.m, info->ray.n);
		if (map_bounderies(info, n) == 1)
			break ;
		if ((hit = hit_map(info, n) == 1))
			break ;
		info->test_axis[n].y += (info->a.y < info->p_of_plan.y)
			? BLOCKSIZE : -BLOCKSIZE;
	}
}

int		map_bounderies(t_info *info, int n)
{
	if ((int)info->test_axis[n].x < 0 || (int)info->test_axis[n].y < 0)
	{
		info->redflag[n] = 1;
		return (1);
	}
	if ((int)info->test_axis[n].x >= (int)(info->mapwidth * BLOCKSIZE)
		|| (int)info->test_axis[n].y >= (int)(info->mapheight * BLOCKSIZE))
	{
		info->redflag[n] = 1;
		return (1);
	}
	return (0);
}

double	distance_to_wall(t_info *info)
{
	double distance[2];

	if (info->redflag[0] == 1 || info->redflag[1] == 1)
		return (cub_redflag(info));
	distance[0] = distance_2_points(info->a, info->test_axis[0]);
	distance[1] = distance_2_points(info->a, info->test_axis[1]);
	if (distance[0] < distance[1])
	{
		info->side = 0;
		info->wall[0] = info->test_axis[0].x;
		info->wall[1] = info->test_axis[0].y;
		return (distance[0]);
	}
	else
	{
		info->side = 1;
		info->wall[0] = info->test_axis[1].x;
		info->wall[1] = info->test_axis[1].y;
		return (distance[1]);
	}
}
