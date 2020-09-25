/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 10:45:34 by lduhamel          #+#    #+#             */
/*   Updated: 2020/09/25 14:27:34 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	ft_free_img(t_info *info, t_img *img)
{
	if (img)
	{
		mlx_destroy_image(info->mlx_ptr, img->img_ptr);
		free(img);
		img = NULL;
	}
}

void	free_tabs(t_info *info)
{
	free_and_init_tab(&info->barrel.x);
	free_and_init_tab(&info->barrel.y);
	free_and_init_tab(&info->barrel.walldist);
	free_and_init_tab(&info->barrel.a);
	free_and_init_tab(&info->barrel.c);
	free_and_init_tab(&info->barrel.dist);
}

void	error_parsing_free(t_maptab *tab)
{
	free_and_init(&tab->line);
	free_and_init(&tab->map_str1);
	free_and_init(&tab->map_str2);
	free_doubletab(tab->tab, tab->counter - 1);
	free_doubletab(tab->sol, tab->counter - 1);
}

void	elem_free(t_info *info, t_maptab *tab)
{
	free_and_init(&tab->line);
	free_and_init(&info->sp_texture);
	free_and_init(&info->no_texture);
	free_and_init(&info->so_texture);
	free_and_init(&info->we_texture);
	free_and_init(&info->ea_texture);
}

void	free_all(t_info *info, t_maptab *tab, int n)
{
	n > 0 ? elem_free(info, tab) : 0;
	n > 1 ? error_parsing_free(tab) : 0;
	n > 2 ? free_doubletab(info->worldmap, info->mapheight - 1) : 0;
	n > 2 ? free_tabs(info) : 0;
	n > 3 ? free_and_init(&info->name_bmp_file) : 0;
	if (n > 4)
	{
		mlx_destroy_image(info->mlx_ptr, info->no.img_ptr);
		mlx_destroy_image(info->mlx_ptr, info->ea.img_ptr);
		mlx_destroy_image(info->mlx_ptr, info->we.img_ptr);
		mlx_destroy_image(info->mlx_ptr, info->so.img_ptr);
		mlx_destroy_image(info->mlx_ptr, info->sp.img_ptr);
		mlx_destroy_image(info->mlx_ptr, info->img->img_ptr);
		if (info->save_flag == 0)
			mlx_destroy_window(info->mlx_ptr, info->win_ptr);
		free(info->img);
	}
	free(info);
}
