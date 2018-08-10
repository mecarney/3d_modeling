/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 17:03:28 by mcarney           #+#    #+#             */
/*   Updated: 2018/07/24 17:03:29 by mcarney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		fill_array(char *filename, t_wf *wf, int y)
{
	int		x;
	int		fd;
	char	**line_split;
	char	*line;

	if (!(fd = open(filename, O_RDONLY)))
		ft_return_error("read error");
	while (ft_get_next_line(fd, &line) == 1)
	{
		line_split = ft_strsplit(line, ' ');
		x = 0;
		while (line_split[x])
			x++;
		(x == wf->file_w) ? 0 : ft_return_error("file width error");
		if (!(wf->pxs[y] = (t_px *)malloc(sizeof(t_px) * wf->file_w)))
			ft_return_error("malloc error");
		x = -1;
		while (++x < wf->file_w)
			wf->pxs[y][x].z = ft_atoi(line_split[x]);
		y++;
		ft_free_array((void**)line_split, wf->file_w);
		free(line);
	}
	(y == wf->file_h) ? 0 : ft_return_error("file height error");
	close(fd);
}

void		count_and_error_check(char *filename, t_wf *wf)
{
	int		fd;
	char	*line;
	char	**line_split;

	if ((fd = open(filename, O_RDONLY)) < 1)
		ft_return_error("read error");
	wf->file_h = 0;
	while (ft_get_next_line(fd, &line) == 1)
	{
		if (!(wf->file_w))
		{
			line_split = ft_strsplit(line, ' ');
			wf->file_w = 0;
			while (line_split[wf->file_w])
				wf->file_w++;
			ft_free_array((void**)line_split, wf->file_w);
		}
		wf->file_h++;
		free(line);
	}
	close(fd);
	if (!(wf->pxs = (t_px **)malloc(sizeof(t_px *) * wf->file_h)))
		ft_return_error("malloc error");
}

int			key_press_hook(int keycode, t_wf *wf)
{
	mlx_destroy_image(wf->mlx, wf->img);
	(keycode == 49) ? defaults(wf) : 0;
	(keycode == 6) ? wf->zoom += 1 : 0;
	(keycode == 7) ? wf->zoom -= 1 : 0;
	(keycode == 18) ? wf->ydegrees += 1 : 0;
	(keycode == 19) ? wf->ydegrees -= 1 : 0;
	(keycode == 20) ? wf->xdegrees += 1 : 0;
	(keycode == 21) ? wf->xdegrees -= 1 : 0;
	(keycode == 22) ? wf->zdegrees += 1 : 0;
	(keycode == 23) ? wf->zdegrees -= 1 : 0;
	(keycode == 124) ? wf->xslide += 5 : 0;
	(keycode == 123) ? wf->xslide -= 5 : 0;
	(keycode == 126) ? wf->yslide -= 5 : 0;
	(keycode == 125) ? wf->yslide += 5 : 0;
	display(wf);
	if (keycode == 53)
	{
		mlx_destroy_window(wf->mlx, wf->win);
		ft_free_array((void **)wf->pxs, wf->file_h);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int			deal_mouse(int button, int x, int y, t_wf *wf)
{
	if (x && y)
	{
		(button == 4) ? wf->zoom += 1 : 0;
		(button == 5) ? wf->zoom -= 1 : 0;
	}
	mlx_destroy_image(wf->mlx, wf->img);
	display(wf);
	return (0);
}
