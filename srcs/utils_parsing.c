/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 23:15:47 by lduhamel          #+#    #+#             */
/*   Updated: 2020/09/22 11:33:35 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		atoi_v1(t_element *elem)
{
	int			i;
	long long	result;
	long long	previous;

	i = 0;
	result = 0;
	previous = 0;
	while (elem->line[elem->i] >= '0' && elem->line[elem->i] <= '9')
	{
		result = result * 10 + (elem->line[elem->i++] - '0');
		if (result < previous || result > 9223372036854775807)
			return (-1);
		previous = result;
	}
	elem->i--;
	return (result);
}

int		is_digit(char c)
{
	return (c >= '0' && c <= '9' ? 1 : 0);
}

int		ft_strlen1(char *s)
{
	int i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup1(char *s1)
{
	char	*ptr;
	int		i;

	if (!s1 || !(ptr = (char*)malloc(sizeof(char) * (ft_strlen1(s1) + 1))))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

void	ft_putstr1(char *s)
{
	int i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
	}
}
