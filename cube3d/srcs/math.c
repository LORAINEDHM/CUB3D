/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 17:29:14 by ssimon            #+#    #+#             */
/*   Updated: 2020/09/19 12:12:29 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

double	toa(double angle, double o)
{
	double a;

	a = o / tan((2 * (double)M_PI) / (360 / angle));
	return (a);
}

double	ft_deg2rad(double degree)
{
	return (degree * M_PI / 180);
}

double	ft_rad2deg(double rad)
{
	return (rad / (PI / 180.0));
}

void	ray(t_ray *ray, t_p a, t_p b)
{
	double temp;

	temp = 0;
	if (b.x - a.x == 0)
		temp = 0.0000001;
	ray->m = (b.y - a.y) / (b.x - a.x + temp);
	ray->n = b.y - (ray->m * b.x);
}

double	distance_2_points(t_p a, t_p b)
{
	return (sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2)));
}
