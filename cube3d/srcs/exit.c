/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 15:10:23 by lduhamel          #+#    #+#             */
/*   Updated: 2020/09/16 15:11:02 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	ft_exit(t_info *info, t_maptab *tab)
{
	mlx_destroy_window(info->mlx_ptr, info->win_ptr);
	info->mlx_ptr = NULL;
	free(info->mlx_ptr);
	exit(0);
	return ;
}

void	texture_free(t_info *info)
{
	free_and_init(&info->sp_texture);
	free_and_init(&info->no_texture);
	free_and_init(&info->so_texture);
	free_and_init(&info->we_texture);
	free_and_init(&info->ea_texture);
}
