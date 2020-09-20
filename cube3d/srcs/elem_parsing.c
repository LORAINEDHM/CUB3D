/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 13:18:04 by lduhamel          #+#    #+#             */
/*   Updated: 2020/09/19 11:55:15 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		parsing(t_element *elem, t_maptab *tab, t_info *info, char **argv)
{
	init_parsing(elem, tab, info);
	if ((elem->fd = open(argv[1], O_RDONLY)) < 0)
		return (-1);
	while (elem->ret == 1)
	{
		elem->i = 0;
		if ((elem->ret = get_next_line(elem->fd, &elem->line)) == -1)
			return (-1);
		if (read_elem(elem, tab, info) < 0)
			return (-1);
		if (elem->nb_flag == 1)
		{
			if (map_to_str(elem, tab, info) == -1)
				return (-1);
		}
		if (elem->line != NULL)
			free_and_init(&elem->line);
		tab->line != NULL ? free_and_init(&tab->line) : 0;
	}
	if (checking_map(tab, info) == -1)
		return (-1);
	close(elem->fd);
	return (0);
}

int		read_elem(t_element *elem, t_maptab *tab, t_info *info)
{
	if (elem->line[0] == '\0')
		return (0);
	if (elem->nb_flag == 0)
	{
		while (elem->line[elem->i] == ' ')
			elem->i++;
		if (elem->line[elem->i] == 'R')
			elem->ret = resolution(elem, info);
		else if (elem->line[elem->i] == 'F' || elem->line[elem->i] == 'C')
			which_color(elem, info);
		else if (elem->line[elem->i] == 'S' || (elem->line[elem->i] == 'N'
				&& elem->line[elem->i + 1] == 'O')
			|| (elem->line[elem->i] == 'S' && elem->line[elem->i + 1] == 'O')
			|| (elem->line[elem->i] == 'W' && elem->line[elem->i + 1] == 'E')
			|| (elem->line[elem->i] == 'E' && elem->line[elem->i + 1] == 'A'))
			bit_texture(elem) >= 0 ? which_texture(elem, info) : 0;
		else
			elem->nb_flag = (nb_elements(elem, tab, info) == 1 ? 1 : 0);
	}
	if (elem->ret < 0)
	{
		error_msg_elem(info, tab, elem, 1);
		return (-1);
	}
	return (0);
}

int		nb_elements(t_element *elem, t_maptab *tab, t_info *info)
{
	if (!(F_F & elem->bitflag) || !(F_C & elem->bitflag)
		|| !(F_R & elem->bitflag) || !(F_SP & elem->bitflag)
		|| !(F_SO & elem->bitflag) || !(F_NO & elem->bitflag)
		|| !(F_WE & elem->bitflag) || !(F_EA & elem->bitflag))
	{
		elem->ret = MISSING_ELEMENT;
		return (0);
	}
	return (1);
}

void	init_rgb(t_element *elem)
{
	elem->r = 0;
	elem->g = 0;
	elem->b = 0;
	elem->flag = 0;
}
