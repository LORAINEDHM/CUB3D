/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 23:11:43 by lduhamel          #+#    #+#             */
/*   Updated: 2020/09/22 11:31:13 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		which_color(t_element *elem, t_info *info)
{
	if (elem->line[elem->i] == 'F')
	{
		if (!(F_F & elem->bitflag))
		{
			elem->bitflag |= F_F;
			if ((info->trgb_floor = color(elem)) < 0)
				elem->ret = info->trgb_floor;
		}
		else
			elem->ret = TOO_MANY_DESCRIPTIONS;
	}
	else if (elem->line[elem->i] == 'C')
	{
		if (!(F_C & elem->bitflag))
		{
			elem->bitflag |= F_C;
			if ((info->trgb_ceiling = color(elem)) < 0)
				elem->ret = info->trgb_ceiling;
		}
		else
			elem->ret = TOO_MANY_DESCRIPTIONS;
	}
	return (1);
}

int		color(t_element *elem)
{
	int ret;
	int trgb;

	trgb = 0;
	init_rgb(elem);
	while (elem->line[++elem->i] != '\0')
	{
		if (elem->line[elem->i] == '-' && is_digit(elem->line[elem->i + 1]))
			return (NONEXISTENT_COLOR);
		else if (is_digit(elem->line[elem->i]))
		{
			if ((ret = if_digit(elem)) < 0)
				return (ret);
		}
		else if (elem->line[elem->i] != ' ')
		{
			return ((elem->flag == 3 && elem->line[elem->i] == ',') ?
				COMMA_ISSUE : INVALID_CHAR_IN_COLOR);
		}
	}
	if (elem->flag != 3)
		return (WRONG_NB_OF_COLOR_NB);
	trgb = 65536 * elem->r + 256 * elem->g + elem->b;
	return (trgb);
}

int		if_digit(t_element *elem)
{
	elem->r = (elem->flag == 0 ? atoi_v1(elem) : elem->r);
	elem->g = (elem->flag == 1 ? atoi_v1(elem) : elem->g);
	elem->b = (elem->flag == 2 ? atoi_v1(elem) : elem->b);
	if (elem->r > 255 || elem->g > 255 || elem->b > 255)
		return (NONEXISTENT_COLOR);
	elem->flag++;
	elem->i = (elem->line[elem->i + 1] != '\0' && elem->flag < 3 ?
				elem->i + 1 : elem->i);
	if (elem->flag < 3)
	{
		while (elem->line[elem->i] != '\0' && elem->line[elem->i] == ' ')
			elem->i++;
		if (elem->line[elem->i] != ',')
			return (COMMA_ISSUE);
	}
	return (1);
}
