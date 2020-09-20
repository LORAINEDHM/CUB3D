/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 17:00:17 by lduhamel          #+#    #+#             */
/*   Updated: 2020/09/12 12:03:57 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		cleanline(t_maptab *tab, t_info *info, char **line, char **newline)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!(*newline = (char*)malloc(sizeof(char) * (ft_strlen1(*line) + 1))))
	{
		tab->error.ret = MALLOC_FAIL;
		return (-1);
	}
	while ((*line)[i] != '\0')
	{
		(*line)[i] = ((*line)[i] == ' ' ? '0' : (*line)[i]);
		tab->error.ret = ft_check_line(tab, info, &tab->line, i);
		if (tab->error.ret < 0)
			return (-1);
		(*newline)[j] = (*line)[i];
		i++;
		j++;
	}
	(*newline)[j] = '\0';
	return (1);
}

int		ft_check_line(t_maptab *tab, t_info *info, char **line, int i)
{
	if ((*line)[i] == 'N' || (*line)[i] == 'E' || (*line)[i] == 'S'
		|| (*line)[i] == 'W' || (*line)[i] == '0' || (*line)[i] == '1'
		|| (*line)[i] == '2')
	{
		if ((*line)[i] == '2')
			info->nbsprite++;
		if ((*line)[i] != '0' && (*line)[i] != '1' && (*line)[i] != '2')
		{
			if (tab->letter == 1)
				return (WRONG_NB_OF_LETTER);
			if (tab->letter == 0)
			{
				(*line)[i] = ((*line)[i] == 'N' ? '3' : (*line)[i]);
				(*line)[i] = ((*line)[i] == 'W' ? '4' : (*line)[i]);
				(*line)[i] = ((*line)[i] == 'S' ? '5' : (*line)[i]);
				(*line)[i] = ((*line)[i] == 'E' ? '6' : (*line)[i]);
				tab->letter = 1;
			}
		}
	}
	else
		return (FORBIDDEN_CHARACTER);
	return (1);
}

char	*ft_join_lines(char *temp, char *line, int counter)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	if (line == NULL || (line == NULL && line == NULL))
		return (NULL);
	if (!(str = (char*)malloc(sizeof(char) * ((ft_strlen1(temp))
		+ (ft_strlen1(line) + 2)))))
		return (NULL);
	while (temp && temp[i])
	{
		str[i] = temp[i];
		i++;
	}
	while (line && line[j])
		str[i++] = line[j++];
	str[i] = '\n';
	str[i + 1] = '\0';
	if (temp != NULL)
		free(temp);
	return (str);
}

int		map_to_str(t_element *elem, t_maptab *tab, t_info *info)
{
	char	*newline;

	tab->line = elem->line;
	elem->line = NULL;
	if (tab->line[0] == '\0')
	{
		tab->error.ret = EMPTY_LINE;
		return (-1);
	}
	if (cleanline(tab, info, &tab->line, &newline) == -1)
	{
		free_and_init(&newline);
		error_msg(info, tab, &tab->error, 1);
		return (-1);
	}
	if ((tab->map_str1 = ft_join_lines(tab->map_str1, newline, tab->counter))
	== NULL)
	{
		tab->error.ret = MALLOC_FAIL;
		error_msg(info, tab, &tab->error, 2);
		return (-1);
	}
	free_and_init(&newline);
	tab->counter++;
	return (1);
}
