/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 16:17:33 by ssimon            #+#    #+#             */
/*   Updated: 2020/09/19 12:10:41 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		ft_key_hit(int keycode, t_info *info, t_maptab *tab)
{
	if (keycode == KEY_UP)
		info->move.up = 1;
	if (keycode == KEY_DOWN)
		info->move.down = 1;
	if (keycode == KEY_RIGHT)
		info->move.right = 1;
	if (keycode == KEY_LEFT)
		info->move.left = 1;
	if (keycode == ROTATE_RIGHT)
		info->move.camr = 1;
	if (keycode == ROTATE_LEFT)
		info->move.caml = 1;
	if (keycode == ESC)
		ft_exit(info, tab);
	return (SUCCESS);
}

int		ft_key_release(int keycode, t_info *info)
{
	if (keycode == KEY_UP)
		info->move.up = 0;
	if (keycode == KEY_DOWN)
		info->move.down = 0;
	if (keycode == KEY_LEFT)
		info->move.left = 0;
	if (keycode == KEY_RIGHT)
		info->move.right = 0;
	if (keycode == ROTATE_RIGHT)
		info->move.camr = 0;
	if (keycode == ROTATE_LEFT)
		info->move.caml = 0;
	return (SUCCESS);
}

int		ft_handle_events(t_info *info, t_maptab *tab)
{
	ft_move(info);
	ft_render_display(info);
	mlx_put_image_to_window(info->mlx_ptr, info->win_ptr,
		info->img->img_ptr, 0, 0);
	if (info->save_flag)
		info->error = cub_save(info);
	if (info->error != SUCCESS)
	{
		free_all(info, tab, 5);
		cub_error_save(info->error);
		ft_exit(info, tab);
	}
	return (SUCCESS);
}

int		events(t_info *info)
{
	if ((info->win_ptr = mlx_new_window(info->mlx_ptr,
		info->screenwidth, info->screenheight, "Cube3D")) == NULL)
		return (ERROR_NEW_WINDOW);
	if ((info->img = ft_new_image(info,
		info->screenwidth, info->screenheight)) == NULL)
		return (ERROR_NEW_IMAGE);
	mlx_hook(info->win_ptr, KEYPRESS, KEYPRESSMASK, ft_key_hit, info);
	mlx_hook(info->win_ptr, KEYRELEASE, KEYRELEASEMASK, ft_key_release, info);
	mlx_loop_hook(info->mlx_ptr, ft_handle_events, info);
	mlx_loop(info->mlx_ptr);
	return (SUCCESS);
}

void	cub_error_save(int error)
{
	if (error == ERROR_MALLOC)
		ft_putstr_fd("ERROR: Heap memory allocation failed\n", 1);
	if (error == ERROR_OPEN_FILE)
		ft_putstr_fd("ERROR: Failed to open the file to save bitmap\n", 1);
	if (error == WRITE_ERROR)
		ft_putstr_fd("ERROR: Write issue in the bitmap file\n", 1);
}
