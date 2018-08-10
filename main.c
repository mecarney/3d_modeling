/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 17:03:23 by mcarney           #+#    #+#             */
/*   Updated: 2018/07/24 17:03:24 by mcarney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		rotations(t_wf *wf, t_px *pt)
{
	float	theta_x;
	float	theta_y;
	float	theta_z;

	theta_x = wf->xdegrees * .017;
	theta_y = wf->ydegrees * .017;
	theta_z = wf->zdegrees * .017;
	pt->tmpy = round(pt->tmpy * cos(theta_x) - pt->z * sin(theta_x));
	pt->tmpx = round(pt->tmpx * cos(theta_y) + pt->z * sin(theta_y));
	pt->tmpx = round(pt->tmpx * cos(theta_z) + pt->tmpy * sin(theta_z));
	pt->tmpy = round(pt->tmpy * cos(theta_z) - pt->tmpx * sin(theta_z));
}

void		calibrate(t_wf *wf)
{
	int		x;
	int		y;

	y = -1;
	while (++y < wf->file_h)
	{
		x = -1;
		while (++x < wf->file_w)
		{
			wf->pxs[y][x].tmpx = wf->zoom * x;
			wf->pxs[y][x].tmpy = wf->zoom * y;
			rotations(wf, &wf->pxs[y][x]);
			wf->pxs[y][x].x = wf->pxs[y][x].tmpx + wf->win_w / 4 + wf->xslide;
			wf->pxs[y][x].y = wf->pxs[y][x].tmpy + wf->win_h / 2 + wf->yslide;
		}
	}
}

void		defaults(t_wf *wf)
{
	wf->win_w = (wf->file_w > wf->file_h ? wf->file_w : wf->file_h) * 10;
	(wf->win_w < 800) ? wf->win_w = 800 : (0);
	(wf->win_w > 1920) ? wf->win_w = 1920 : (0);
	wf->win_h = wf->win_w * 9 / 16;
	wf->xdegrees = 75;
	wf->ydegrees = -1;
	wf->zdegrees = 0;
	wf->zoom = wf->win_h / (wf->file_w > wf->file_h ? wf->file_w : wf->file_h);
	if (!wf->zoom)
		wf->zoom = 2;
	wf->xslide = 0;
	wf->yslide = 0;
	wf->color = 0x005cadce;
}

int			main(int ac, char **av)
{
	t_wf	wf;

	if (ac != 2 && ac != 3)
		return (ft_return_error("usage: ./fdf <filename> [unsigned integer]"));
	wf.file_w = 0;
	count_and_error_check(av[1], &wf);
	fill_array(av[1], &wf, 0);
	defaults(&wf);
	if (!(wf.mlx = mlx_init()) ||
		!(wf.win = mlx_new_window(wf.mlx, wf.win_w, wf.win_h + 100, av[1])))
		ft_return_error("mlx error");
	if (ac == 3 && !(wf.color = (unsigned int)ft_atoi(av[2])))
		wf.color = 0x00588699;
	(wf.color > 2007483648) ? wf.color = 0x005cadce : 0;
	decorate_win(wf.mlx, wf.win, 40, wf.win_h);
	display(&wf);
	mlx_hook(wf.win, 2, 0, key_press_hook, &wf);
	mlx_mouse_hook(wf.win, deal_mouse, &wf);
	mlx_loop(wf.mlx);
	return (0);
}
