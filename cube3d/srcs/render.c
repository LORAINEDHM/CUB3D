/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 13:37:32 by lduhamel          #+#    #+#             */
/*   Updated: 2020/09/20 23:11:45 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	ft_render_display(t_info *info)
{
	int		whichray;
	double	shortest_distance;
	double	wall_height;

	whichray = 0;
	info->wall[0] = -1;
	info->wall[1] = -1;
	while (whichray < info->screenwidth)
	{
		update_info(info);
		p_on_plan(info, (double)whichray);
		ray(&info->ray, info->a, info->p_of_plan);
		info->barrel.a[whichray] = info->ray.m;
		info->barrel.c[whichray] = info->ray.n;
		test_x_axis(info);
		test_y_axis(info);
		shortest_distance = distance_to_wall(info);
		info->barrel.walldist[whichray] = shortest_distance;
		wall_height = walls(info, shortest_distance, whichray);
		ft_display(info, whichray, wall_height);
		whichray++;
	}
	handlesprites(info);
}

void	ft_display(t_info *info, int whichray, double wall_height)
{
	double	color;
	double	ratio;
	double	rest;

	info->tex_y = 0;
	ratio = 64 / wall_height;
	if (wall_height > info->screenheight)
		info->tex_y = ((wall_height - info->screenheight) / 2) * ratio;
	if (info->side == 1)
	{
		if ((rest = info->wall[0] % 64) != 0)
			info->tex_x = rest;
		else
			info->tex_x = 0;
	}
	if (info->side == 0)
	{
		if ((rest = info->wall[1] % 64) != 0)
			info->tex_x = rest;
		else
			info->tex_x = 0;
	}
	display_1(info, whichray, wall_height, color);
}

void	display_1(t_info *info, int whichray, double wall_height, double color)
{
	int		*texture;
	float	wall_down;
	double	ratio;
	int		y;

	ratio = 64 / wall_height;
	y = 0;
	wall_down = (info->screenheight - wall_height) / 2;
	texture = display_2(info);
	while (y < info->screenheight)
	{
		while (y < info->screenheight && y < wall_down)
			ft_put_in_img(info, whichray, y++, info->trgb_ceiling);
		while (y < info->screenheight && y < (wall_down + wall_height))
		{
			info->tex_y = info->tex_y + ratio;
			if ((int)info->tex_y >= 64)
				break ;
			color = texture[(int)info->tex_x + (int)info->tex_y * 64];
			ft_put_in_img(info, whichray, y++, color);
		}
		if (y < info->screenheight)
			ft_put_in_img(info, whichray, y++, info->trgb_floor);
	}
}

int		*display_2(t_info *info)
{
	nesw(info);
	if (info->nesw == 0)
		return (info->no.img_data);
	else if (info->nesw == 1)
		return (info->ea.img_data);
	else if (info->nesw == 2)
		return (info->so.img_data);
	else
		return (info->we.img_data);
}
