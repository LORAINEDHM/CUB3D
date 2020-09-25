/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 18:15:15 by lduhamel          #+#    #+#             */
/*   Updated: 2020/09/22 10:17:17 by lduhamel         ###   ########.fr       */
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

void	free_and_init_tab(double **tab)
{
	if (*tab != NULL)
	{
		free(*tab);
		*tab = NULL;
	}
}

void	free_doubletab(int **tab, int i)
{
	if (tab != NULL && *tab != NULL)
	{
		while (i > -1)
		{
			if (tab[i] != NULL)
			{
				free(tab[i]);
				tab[i] = NULL;
			}
			i--;
		}
		free(tab);
		tab = NULL;
	}
}
