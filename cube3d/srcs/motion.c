/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 12:12:43 by lduhamel          #+#    #+#             */
/*   Updated: 2020/09/19 12:12:45 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	ft_move(t_info *info)
{
	if (info->move.up == 1)
		motion(info, FORWARD, 0);
	if (info->move.down == 1)
		motion(info, BACKWARD, 0);
	if (info->move.right == 1)
		motion(info, RIGHT, TRANSLATE_RIGHT);
	if (info->move.left == 1)
		motion(info, LEFT, TRANSLATE_LEFT);
	if (info->move.camr == 1)
		ft_angle(info);
	if (info->move.caml == 1)
		ft_angle(info);
}

void	motion(t_info *info, int motion, int translation)
{
	double displacement[2];

	displacement[0] = motion *
		cos(ft_deg2rad(info->angle + translation)) * SPEED;
	displacement[1] = motion *
		sin(ft_deg2rad(info->angle + translation)) * SPEED;
	if (allowed_motion(info, displacement))
	{
		info->a.x += round(displacement[0]);
		info->a.y += round(displacement[1]);
		cub_avoid_wall_edge(info);
	}
}

void	cub_avoid_wall_edge(t_info *info)
{
	double displacement[2];

	ft_bzero(displacement, sizeof(double) * 2);
	if ((int)info->a.x % BLOCKSIZE == 0)
	{
		displacement[0] = 1;
		if (allowed_motion(info, displacement))
			info->a.x += displacement[0];
		else
			info->a.x -= displacement[0];
		displacement[0] = 0;
	}
	if ((int)info->a.y % BLOCKSIZE == 0)
	{
		displacement[1] = 1;
		if (allowed_motion(info, displacement))
			info->a.y += displacement[1];
		else
			info->a.y -= displacement[1];
	}
	return ;
}

void	ft_angle(t_info *info)
{
	if (info->move.caml == 1)
		(info->angle) += SENSITIVITY;
	if (info->move.camr == 1)
	{
		(info->angle) -= SENSITIVITY;
		if (info->angle < 0)
			info->angle = 360 + info->angle;
	}
	if (info->angle >= 360)
		info->angle -= 360;
}

int		allowed_motion(t_info *info, double *displacement)
{
	t_p		position_proposal;
	t_map	map_check;

	position_proposal.x = info->a.x + displacement[0];
	position_proposal.y = info->a.y + displacement[1];
	map_check.x = bloc_to_map(position_proposal.x, BLOCKSIZE);
	map_check.y = bloc_to_map(position_proposal.y, BLOCKSIZE);
	if (inside_map(info, map_check))
	{
		if (avoid_wall(map_check, info))
		{
			return (1);
		}
	}
	return (0);
}
