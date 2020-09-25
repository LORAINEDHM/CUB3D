/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 14:17:35 by lduhamel          #+#    #+#             */
/*   Updated: 2020/09/25 16:14:51 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		resolution(t_element *elem, t_info *info)
{
	int ret;

	ret = 1;
	if (!(F_R & elem->bitflag))
	{
		elem->bitflag |= F_R;
		elem->flag = 0;
		while (elem->line[++elem->i] != '\0')
		{
			if ((ret = checking_resolution_line(elem, info)) < 1)
				return (ret);
		}
		init_resolution(info);
		return (elem->flag == 2 ? 1 : WRONG_NB_OF_RESOLUTION_NB);
	}
	else
		return (TOO_MANY_DESCRIPTIONS);
	return (1);
}

int		checking_resolution_line(t_element *elem, t_info *info)
{
	if (elem->line[elem->i] == '-' && is_digit(elem->line[elem->i + 1]))
		return (NEGATIVE_NB);
	else if (is_digit(elem->line[elem->i]))
	{
		if (elem->flag == 0)
			info->screenwidth = atoi_v1(elem);
		if (elem->flag == 1)
			info->screenheight = atoi_v1(elem);
		elem->flag++;
	}
	else if (elem->line[elem->i] != ' ')
		return (INVALID_CHAR_IN_RESOLUTION);
	return (1);
}

void	init_resolution(t_info *info)
{
	info->screenwidth = (info->screenwidth > 3200 ? 3200 : info->screenwidth);
	info->screenwidth = (info->screenwidth < 320 ? 320 : info->screenwidth);
	info->screenheight = (info->screenheight > 1800 ?
		1800 : info->screenheight);
	info->screenheight = (info->screenheight < 200 ? 200 : info->screenheight);
}
