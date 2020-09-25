/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 10:57:45 by lduhamel          #+#    #+#             */
/*   Updated: 2020/09/25 14:40:58 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		main(int ac, char **argv)
{
	t_info		*info;
	t_maptab	tab;
	t_element	elem;

	if (!(info = malloc(sizeof(t_info))))
	{
		ft_putstr_fd("ERROR: Heap memory allocation failed\n", 1);
		return (-1);
	}
	ft_bzero(info, sizeof(t_info));
	if (cub_check_ac_argv(info, ac, argv) != SUCCESS)
	{
		free(info);
		return (0);
	}
	if (parsing(&elem, &tab, info, argv) == -1)
		return (0);
	info->worldmap = tab.tab;
	if (ft_init(info, &tab) == -1)
		return (-1);
	info->mlx_ptr = mlx_init();
	put_texture(info);
	cub_main(info, &tab);
	return (0);
}

void	cub_main(t_info *info, t_maptab *tab)
{
	if ((info->error = events(info)) != SUCCESS)
	{
		cub_error_events(info->error);
		ft_exit();
	}
}

void	cub_error_events(int error)
{
	if (error == ERROR_NEW_IMAGE)
		ft_putstr_fd("ERROR: Heap memory allocation failed\n", 1);
	if (error == ERROR_NEW_WINDOW)
		ft_putstr_fd("ERROR: Failed to open a new window\n", 1);
}

void	nesw(t_info *info)
{
	if (info->side == 0)
		info->nesw = (info->a.x < info->p_of_plan.x) ? 1 : 3;
	if (info->side == 1)
		info->nesw = (info->a.y < info->p_of_plan.y) ? 0 : 2;
	return ;
}
