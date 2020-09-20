/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 14:30:49 by lduhamel          #+#    #+#             */
/*   Updated: 2020/09/11 14:35:48 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_img	*ft_new_image(t_info *info, int screenwidth, int screenheight)
{
	t_img	*img;

	if (!(img = malloc(sizeof(t_img))))
		return (NULL);
	if (!(img->img_ptr = mlx_new_image(info->mlx_ptr, screenwidth,
	screenheight)))
		return (NULL);
	if (!(img->img_data = (int *)mlx_get_data_addr(img->img_ptr, &img->bpp,
		&img->size_line, &img->endian)))
		return (NULL);
	img->width = screenwidth;
	img->height = screenheight;
	return (img);
}

void	update_info(t_info *info)
{
	info->dir.x = cos(ft_deg2rad(info->angle)) * info->ad;
	info->dir.y = sin(ft_deg2rad(info->angle)) * info->ad;
	info->plan.x = cos(ft_deg2rad(info->angle + 90)) * info->bd;
	info->plan.y = sin(ft_deg2rad(info->angle + 90)) * info->bd;
	info->b.x = info->a.x + info->dir.x + info->plan.x;
	info->b.y = info->a.y + info->dir.y + info->plan.y;
	info->c.x = info->a.x + info->dir.x - info->plan.x;
	info->c.y = info->a.y + info->dir.y - info->plan.y;
	info->next_axis_x = (int)info->a.x
		+ BLOCKSIZE - ((int)info->a.x % BLOCKSIZE);
	info->next_axis_y = (int)info->a.y
		+ BLOCKSIZE - ((int)info->a.y % BLOCKSIZE);
}

void	ft_put_in_img(t_info *info, int x, int y, int color)
{
	info->img->img_data[info->screenwidth * y + x] = color;
}

void	put_texture(t_info *info)
{
	int size;

	size = BLOCKSIZE;
	info->no.img_ptr = mlx_xpm_file_to_image
(info->mlx_ptr, info->no_texture, &size, &size);
	info->no.img_data = (int *)mlx_get_data_addr
(info->no.img_ptr, &info->no.bpp, &info->no.size_line, &info->no.endian);
	info->so.img_ptr = mlx_xpm_file_to_image
(info->mlx_ptr, info->so_texture, &size, &size);
	info->so.img_data = (int *)mlx_get_data_addr
(info->so.img_ptr, &info->so.bpp, &info->so.size_line, &info->so.endian);
	info->we.img_ptr = mlx_xpm_file_to_image
(info->mlx_ptr, info->we_texture, &size, &size);
	info->we.img_data = (int *)mlx_get_data_addr
(info->we.img_ptr, &info->we.bpp, &info->we.size_line, &info->we.endian);
	info->ea.img_ptr = mlx_xpm_file_to_image
(info->mlx_ptr, info->ea_texture, &size, &size);
	info->ea.img_data = (int *)mlx_get_data_addr
(info->ea.img_ptr, &info->ea.bpp, &info->ea.size_line, &info->ea.endian);
	info->sp.img_ptr = mlx_xpm_file_to_image
(info->mlx_ptr, info->sp_texture, &size, &size);
	info->sp.img_data = (int *)mlx_get_data_addr
(info->sp.img_ptr, &info->sp.bpp, &info->sp.size_line, &info->sp.endian);
}
