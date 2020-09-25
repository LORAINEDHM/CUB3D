/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 15:10:23 by lduhamel          #+#    #+#             */
/*   Updated: 2020/09/25 16:12:14 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	ft_exit(void)
{
	exit(0);
	return ;
}

int		ft_free_and_exit(t_info *info)
{
	free_all(info, &info->tab, 5);
	exit(0);
	return (1);
}

void	texture_free(t_info *info)
{
	free_and_init(&info->sp_texture);
	free_and_init(&info->no_texture);
	free_and_init(&info->so_texture);
	free_and_init(&info->we_texture);
	free_and_init(&info->ea_texture);
}
