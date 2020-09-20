/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 18:15:15 by lduhamel          #+#    #+#             */
/*   Updated: 2020/09/11 14:36:49 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	free_and_init(char **variable)
{
	if (*variable != NULL)
	{
		free(*variable);
		*variable = NULL;
	}
}

void	free_and_init_tab(double *tab)
{
	if (tab != 0)
	{
		free(tab);
		tab = 0;
	}
}

void	free_doubletab(int **tab, int i)
{
	if (tab != 0)
	{
		while (i > -1)
		{
			if (tab[i] != NULL)
				free(tab[i]);
			i--;
		}
		tab[0] = NULL;
	}
}
