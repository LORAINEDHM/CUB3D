/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 14:12:29 by lduhamel          #+#    #+#             */
/*   Updated: 2020/09/23 17:01:29 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		which_texture(t_element *elem, t_info *info)
{
	elem->texture_flag = 1;
	if (elem->line[elem->i] == 'S' && elem->line[elem->i + 1] != 'O')
	{
		elem->texture_flag = 0;
		info->sp_texture = texture(elem, info);
	}
	else if (elem->line[elem->i] == 'N' && elem->line[elem->i + 1] == 'O')
		info->no_texture = texture(elem, info);
	else if (elem->line[elem->i] == 'S' && elem->line[elem->i + 1] == 'O')
		info->so_texture = texture(elem, info);
	else if (elem->line[elem->i] == 'W' && elem->line[elem->i + 1] == 'E')
		info->we_texture = texture(elem, info);
	else if (elem->line[elem->i] == 'E' && elem->line[elem->i + 1] == 'A')
		info->ea_texture = texture(elem, info);
	return (elem->ret);
}

char	*texture(t_element *elem, t_info *info)
{
	int		n;
	char	*path;

	n = 0;
	path = NULL;
	elem->i = (elem->texture_flag == 1 ? 2 : 1);
	if (elem->line[elem->i] != ' ')
	{
		elem->ret = MISSING_SPACE;
		return (NULL);
	}
	while (elem->line[elem->i] == ' ' && elem->line[elem->i + 1] != '\0')
		elem->i++;
	if ((path = creating_path(elem, info, n)) == NULL)
		return (NULL);
	if (open(path, O_WRONLY) == -1)
	{
		elem->ret = INVALID_PATH_TEXTURE;
		return (NULL);
	}
	return (path);
}

char	*creating_path(t_element *elem, t_info *info, int n)
{
	char	*path;

	path = NULL;
	while (elem->line[elem->i] != ' ' && elem->line[elem->i] != '\0')
	{
		n++;
		elem->i++;
	}
	if (!(path = malloc(sizeof(char) * n + 1)))
	{
		elem->ret = MALLOC_FAILED;
		return (NULL);
	}
	texture_copy(elem, info, path, n);
	if (elem->ret < 0)
		return (NULL);
	return (path);
}

int		texture_copy(t_element *elem, t_info *info, char *path, int n)
{
	int j;

	j = 0;
	elem->i -= n;
	while (elem->line[elem->i] != ' ' && elem->line[elem->i] != '\0')
	{
		path[j] = elem->line[elem->i];
		j++;
		elem->i++;
	}
	path[j] = '\0';
	while (elem->line[elem->i] != '\0')
	{
		if (elem->line[elem->i] == ' ')
			elem->i++;
		else
		{
			elem->ret = INVALID_TEXTURE_DESCRIPTION;
			return (-1);
		}
	}
	return (1);
}

int		bit_texture(t_element *elem)
{
	int flag;

	if (elem->line[elem->i] == 'S' && elem->line[elem->i + 1] != 'O')
		flag = F_SP;
	else if (elem->line[elem->i] == 'N' && elem->line[elem->i + 1] == 'O')
		flag = F_NO;
	else if (elem->line[elem->i] == 'S' && elem->line[elem->i + 1] == 'O')
		flag = F_SO;
	else if (elem->line[elem->i] == 'W' && elem->line[elem->i + 1] == 'E')
		flag = F_WE;
	else if (elem->line[elem->i] == 'E' && elem->line[elem->i + 1] == 'A')
		flag = F_EA;
	if (!(flag & elem->bitflag))
		elem->bitflag |= flag;
	else
		elem->ret = TOO_MANY_DESCRIPTIONS;
	return (elem->ret);
}
