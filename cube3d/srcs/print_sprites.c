/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 15:53:41 by lduhamel          #+#    #+#             */
/*   Updated: 2020/09/17 13:04:31 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		print_sprite_middle(t_info *info, int i)
{
	print_sprite_left(info, i, info->barrel.middleray, 31);
	print_sprite_right(info, i, info->barrel.middleray, 31);
}

void		print_sprite_right(t_info *info, int i, int whichray, double tex_x)
{
	info->y = info->barrel.ystart;
	info->ratio = 0;
	info->tex_y = 0;
	while (tex_x >= 0 && whichray >= 0)
	{
		print_sprite_right2(info, i, whichray, tex_x);
		info->tex_y = 0;
		info->y = info->barrel.ystart;
		tex_x -= info->ratio;
		whichray--;
	}
}

void		print_sprite_right2(t_info *info, int i, int whichray, double tex_x)
{
	while (info->y < info->screenheight
	&& info->y < (info->barrel.ystart + info->barrel.height) && whichray >= 0)
	{
		info->tex_y = info->tex_y + info->ratio;
		if ((int)info->tex_y >= 64)
			break ;
		if (tex_x < 64
		&& info->barrel.walldist[whichray] > info->barrel.dist[i])
		{
			if ((info->sp.img_data[(int)tex_x + (int)info->tex_y * 64]) != 0)
				info->barrel.color = info->sp.img_data[(int)tex_x
				+ (int)info->tex_y * 64];
		}
		if (tex_x < 64 && (info->y >= 0
		&& info->sp.img_data[(int)tex_x + (int)info->tex_y * 64]) != 0
		&& info->barrel.walldist[whichray] > info->barrel.dist[i])
			ft_put_in_img(info, whichray, info->y, info->barrel.color);
		info->y++;
		info->ratio = 64 / info->barrel.height;
	}
}

void		print_sprite_left(t_info *info, int i, int whichray, double tex_x)
{
	info->y = info->barrel.ystart;
	info->ratio = 0;
	info->tex_y = 0;
	while (tex_x < 64 && whichray < info->screenwidth)
	{
		print_sprite_left2(info, i, whichray, tex_x);
		info->tex_y = 0;
		info->y = info->barrel.ystart;
		tex_x += info->ratio;
		whichray++;
	}
}

void		print_sprite_left2(t_info *info, int i, int whichray, double tex_x)
{
	while (info->y < info->screenheight
	&& info->y < (info->barrel.ystart + info->barrel.height)
	&& whichray < info->screenwidth)
	{
		info->tex_y = info->tex_y + info->ratio;
		if ((int)info->tex_y >= 64)
			break ;
		if (info->barrel.walldist[whichray] > info->barrel.dist[i])
		{
			if ((info->sp.img_data[(int)tex_x + (int)info->tex_y * 64]) != 0)
				info->barrel.color = info->sp.img_data[(int)tex_x
				+ (int)info->tex_y * 64];
		}
		if ((info->y >= 0
		&& info->sp.img_data[(int)tex_x + (int)info->tex_y * 64]) != 0
		&& info->barrel.walldist[whichray] > info->barrel.dist[i])
			ft_put_in_img(info, whichray, info->y, info->barrel.color);
		info->y++;
		info->ratio = 64 / info->barrel.height;
	}
}
