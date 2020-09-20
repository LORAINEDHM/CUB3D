/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 12:13:14 by lduhamel          #+#    #+#             */
/*   Updated: 2020/09/19 12:13:16 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static int	cub_write_header(int fd, t_info *info)
{
	char	c;
	int		d;

	c = 'B';
	if (write(fd, &c, 1) != 1)
		return (WRITE_ERROR);
	c = 'M';
	if (write(fd, &c, 1) != 1)
		return (WRITE_ERROR);
	d = 26 + info->screenwidth * info->screenheight * 3;
	if (write(fd, &d, 4) != 4)
		return (WRITE_ERROR);
	d = 0;
	if (write(fd, &d, 4) != 4)
		return (WRITE_ERROR);
	d = 26;
	if (write(fd, &d, 4) != 4)
		return (WRITE_ERROR);
	return (SUCCESS);
}

static int	cub_write_dib(int fd, t_info *info)
{
	int				d;
	unsigned short	s;

	d = 12;
	if (write(fd, &d, 4) != 4)
		return (WRITE_ERROR);
	s = info->screenwidth;
	if (write(fd, &s, 2) != 2)
		return (WRITE_ERROR);
	s = info->screenheight;
	if (write(fd, &s, 2) != 2)
		return (WRITE_ERROR);
	s = 1;
	if (write(fd, &s, 2) != 2)
		return (WRITE_ERROR);
	s = 24;
	if (write(fd, &s, 2) != 2)
		return (WRITE_ERROR);
	return (SUCCESS);
}

static int	cub_write_data(int fd, t_info *info)
{
	int x;
	int y;
	int color;

	y = 0;
	while (y < info->screenheight)
	{
		x = 0;
		while (x < info->screenwidth)
		{
			color = info->img->img_data[(info->screenheight * info->screenwidth)
				- (info->screenwidth * y - x)];
			if (write(fd, &color, 3) != 3)
				return (WRITE_ERROR);
			++x;
		}
		++y;
	}
	return (SUCCESS);
}

static int	cub_set_filename(char **pathname)
{
	char			*temp;
	unsigned int	i;
	int				j;

	i = ft_strlen(*pathname);
	j = 0;
	while (pathname[0][i] != '/' && i > 0)
		i--;
	while (pathname[0][i + j] != '\0')
	{
		pathname[0][j] = pathname[0][i + j];
		j++;
	}
	pathname[0][j] = 0;
	if ((temp = ft_strjoin("pics", *pathname)) == NULL)
		return (ERROR_MALLOC);
	free(*pathname);
	*pathname = temp;
	pathname[0][strlen(*pathname) - 3] = 'b';
	pathname[0][strlen(*pathname) - 2] = 'm';
	pathname[0][strlen(*pathname) - 1] = 'p';
	return (SUCCESS);
}

int			cub_save(t_info *info)
{
	int	fd;

	if (cub_set_filename(&info->name_bmp_file) != SUCCESS)
		return (ERROR_MALLOC);
	if ((fd = open(info->name_bmp_file, O_WRONLY | O_CREAT, 0644)) == -1)
	{
		ft_putstr_fd("Error\nIn open : the file must not already exist.\n", 0);
		return (ERROR_OPEN_FILE);
	}
	if ((cub_write_header(fd, info)) != SUCCESS || (cub_write_dib(fd, info))
		!= SUCCESS || (cub_write_data(fd, info)) != SUCCESS)
	{
		close(fd);
		return (WRITE_ERROR);
	}
	close(fd);
	ft_putstr_fd("The file has been created.\n", 0);
	info->save_flag = 0;
	free(info->name_bmp_file);
	return (SUCCESS);
}
