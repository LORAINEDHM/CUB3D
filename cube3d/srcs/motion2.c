/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 12:12:53 by lduhamel          #+#    #+#             */
/*   Updated: 2020/09/19 12:12:56 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
**Checks if we the proposal of coordinates is inside the map
**Not mandatory if map is surrounded by walls
*/

int		inside_map(t_info *info, t_map coordinates)
{
	if (coordinates.x >= 0 && coordinates.x < info->mapwidth)
	{
		if ((coordinates.y >= 0 && coordinates.y < info->mapheight))
			return (1);
	}
	return (0);
}

/*
**Checks if we don't move into a wall
**maybe other constraints will be added
*/

int		avoid_wall(t_map coordinates, t_info *info)
{
	if ((info->worldmap[(info->mapheight - 1)
		- coordinates.y][coordinates.x] != 1)
		&& (info->worldmap[(info->mapheight - 1)
		- coordinates.y][coordinates.x] != 2))
		return (1);
	return (0);
}
