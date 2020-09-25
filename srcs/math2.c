/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 23:14:06 by lduhamel          #+#    #+#             */
/*   Updated: 2020/09/22 11:32:31 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	find_y(t_p *a, double m, double n)
{
	a->y = (m * a->x) + n;
	return ;
}

void	find_x(t_p *a, double m, double n)
{
	a->x = (a->y - n) / m;
	return ;
}

int		bloc_to_map(double position, double blocksize)
{
	return (floor((int)position / (int)blocksize));
}

double	ft_distpointdroite(t_p p, t_droite e)
{
	return (fabs((e.a * p.x + e.b * p.y + e.c)
		/ sqrt(pow(e.a, 2) + pow(e.b, 2))));
}
