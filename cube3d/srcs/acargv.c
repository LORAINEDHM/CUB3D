/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acargv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 12:11:33 by lduhamel          #+#    #+#             */
/*   Updated: 2020/09/19 12:11:37 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		cub_check_ac_argv(t_info *info, int ac, char **argv)
{
	int error;

	if ((error = cub_check_nb_of_arg(ac)) != SUCCESS)
		return (error);
	if (ac >= 2)
	{
		if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) != 0)
		{
			cub_ac_argv_error(FILE_EXT_ERROR);
			return (FILE_EXT_ERROR);
		}
	}
	if (ac == 3)
	{
		if (ft_strncmp(argv[2], "--save", 7) != 0)
		{
			cub_ac_argv_error(SAVE_FLAG_ERROR);
			return (SAVE_FLAG_ERROR);
		}
		info->name_bmp_file = ft_strdup(argv[1]);
		info->save_flag = 1;
	}
	return (SUCCESS);
}

int		cub_check_nb_of_arg(int ac)
{
	if (ac > 3)
	{
		cub_ac_argv_error(NB_ARG_ERROR_TOO_MANY);
		return (NB_ARG_ERROR_TOO_MANY);
	}
	if (ac < 2)
	{
		cub_ac_argv_error(NB_ARG_ERROR_TOO_FEW);
		return (NB_ARG_ERROR_TOO_FEW);
	}
	return (SUCCESS);
}

void	cub_ac_argv_error(int error)
{
	if (error == NB_ARG_ERROR_TOO_MANY)
	{
		ft_putstr_fd("ERROR: Too many arguments.", 1);
		ft_putstr_fd(" Try ./cub3D maps/<yourfile>.cub --save(optional)\n", 1);
	}
	if (error == NB_ARG_ERROR_TOO_FEW)
	{
		ft_putstr_fd("ERROR: Too few arguments.", 1);
		ft_putstr_fd(" Try ./cub3D maps/<yourfile>.cub --save(optional)\n", 1);
	}
	if (error == FILE_EXT_ERROR)
	{
		ft_putstr_fd("ERROR: Wrong file extention.", 1);
		ft_putstr_fd(" Try ./cub3D maps/<yourfile>.cub --save(optional)\n", 1);
	}
	if (error == SAVE_FLAG_ERROR)
	{
		ft_putstr_fd("ERROR: Wrong use of --save flag.", 1);
		ft_putstr_fd(" Try ./cub3D maps/<yourfile>.cub --save(optional)\n", 1);
	}
}
