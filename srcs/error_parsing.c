/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 23:12:05 by lduhamel          #+#    #+#             */
/*   Updated: 2020/09/23 16:09:47 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	error_msg_elem(t_info *info, t_maptab *tab, t_element *elem, int n)
{
	if (elem->ret < 0)
	{
		free_all(info, tab, n);
		ft_putstr1("Error\n");
		if (elem->ret == MISSING_SPACE)
		{
			ft_putstr1("A space is required after the ");
			ft_putstr1("identication letter(s) of the element");
		}
		if (elem->ret == INVALID_CHAR_IN_RESOLUTION)
			ft_putstr1("Resolution information must only be 2 numbers\n");
		if (elem->ret == WRONG_NB_OF_RESOLUTION_NB)
		{
			ft_putstr1("Resolution information must be 2 numbers, ");
			ft_putstr1("not less, not more\n");
		}
		if (elem->ret == NEGATIVE_NB)
			ft_putstr1("The numbers must be >= 0\n");
		if (elem->ret == COMMA_ISSUE)
		{
			ft_putstr1("The 3 color numbers must be separated by a comma ;");
			ft_putstr1("(spaces allowed) /! no comma after the 3rd number\n");
		}
		error_msg_elem2(info, tab, elem, n);
	}
}

void	error_msg_elem2(t_info *info, t_maptab *tab, t_element *elem, int n)
{
	if (elem->ret == NONEXISTENT_COLOR)
		ft_putstr1("Color numbers must be >= 0 and <= 255\n");
	if (elem->ret == WRONG_NB_OF_COLOR_NB)
		ft_putstr1("Color information must be 3 numbers, not less, not more\n");
	if (elem->ret == INVALID_CHAR_IN_COLOR)
		ft_putstr1("Color information must only be 3 numbers\n");
	if (elem->ret == INVALID_TEXTURE_DESCRIPTION)
	{
		ft_putstr1("Texture description must only be a path ");
		ft_putstr1("(spaces allowed before and after the path)\n");
	}
	if (elem->ret == INVALID_PATH_TEXTURE)
		ft_putstr1("Texture path is invalid\n");
	if (elem->ret == TOO_MANY_DESCRIPTIONS)
		ft_putstr1("Only 1 description per element please\n");
	if (elem->ret == MISSING_ELEMENT)
		ft_putstr1("An element is missing (needed 8)\n");
	if (elem->ret == MALLOC_FAILED)
		ft_putstr1("Malloc failed\n");
}

void	error_msg(t_info *info, t_maptab *tab, t_error *error, int n)
{
	if (error->ret < 0)
	{
		free_all(info, tab, n);
		ft_putstr1("Error\n");
		if (error->ret == MAP_NOT_CLOSED)
			ft_putstr1("Map must be closed by walls\n");
		if (error->ret == WRONG_NB_OF_LETTER)
			ft_putstr1("Map must have one position letter\n");
		if (error->ret == FORBIDDEN_CHARACTER)
			ft_putstr1("Map must only have 0, 1, 2, N, W, S or E\n");
		if (error->ret == EMPTY_LINE)
			ft_putstr1("Map must not have empty line\n");
		if (error->ret == DIAGONAL_WALL)
			ft_putstr1("Map must not have diagonal walls\n");
		if (error->ret == MALLOC_FAIL)
			ft_putstr1("Malloc failed\n");
	}
}
