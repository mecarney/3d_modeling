/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 05:59:45 by mcarney           #+#    #+#             */
/*   Updated: 2018/07/31 05:59:46 by mcarney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		light_pixel(t_wf *wf, int x, int y, unsigned int color)
{
	int i;

	if (wf->endian == 0 && x < wf->win_w && y < wf->win_h && x > 0 && y > 0)
	{
		i = 0;
		while (i != wf->bpp / 8)
		{
			wf->addr[y * wf->bytes + x * (wf->bpp / 8) + i++] = color;
			wf->addr[y * wf->bytes + x * (wf->bpp / 8) + i++] = color >> 8;
			wf->addr[y * wf->bytes + x * (wf->bpp / 8) + i++] = color >> 16;
			i++;
		}
	}
}

void		draw_line(t_wf *wf, t_px pt1, t_px pt2, int i)
{
	float	m;
	float	b;
	int		x;
	int		y;

	if (pt2.x == pt1.x && wf->endian == 0)
		m = 2147483647;
	else
		m = (float)(pt2.y - pt1.y) / (pt2.x - pt1.x);
	b = (float)pt1.y - m * pt1.x;
	x = pt1.x;
	while (x != pt2.x)
	{
		y = round(m * x + b);
		light_pixel(wf, x, y, wf->color + (pt1.z + pt2.z) * i++);
		x += ((pt2.x - pt1.x) / abs(pt2.x - pt1.x));
	}
	i = 1;
	y = pt1.y;
	while (y != pt2.y && wf->endian == 0)
	{
		x = round((y - b) / m);
		light_pixel(wf, x, y, wf->color + (pt1.z + pt2.z) * i++);
		y += ((pt2.y - pt1.y) / abs(pt2.y - pt1.y));
	}
}

void		display(t_wf *wf)
{
	int		x;
	int		y;

	wf->img = mlx_new_image(wf->mlx, wf->win_w, wf->win_h);
	wf->addr = mlx_get_data_addr(wf->img, &wf->bpp, &wf->bytes, &wf->endian);
	calibrate(wf);
	y = -1;
	while (++y < wf->file_h)
	{
		x = -1;
		while (++x < wf->file_w)
		{
			if (x != wf->file_w - 1)
				draw_line(wf, wf->pxs[y][x], wf->pxs[y][x + 1], 1);
			if (y != wf->file_h - 1)
				draw_line(wf, wf->pxs[y][x], wf->pxs[y + 1][x], 1);
		}
	}
	mlx_put_image_to_window(wf->mlx, wf->win, wf->img, 0, 0);
}

void		decorate_win(void *a, void *b, int x, int y)
{
	if (x)
	{
		mlx_string_put(a, b, x + 100, y, 0x00FFFFFF, "Quit");
		mlx_string_put(a, b, x + 104, y + 20, 0x00FFFFFF, "Esc");
		mlx_string_put(a, b, x + 24, y + 55, 0x00FFFFFF, "Tri-axial Rotations");
		mlx_string_put(a, b, x, y + 75, 0x00FFFFFF, "X: 1, 2 Y: 3, 4 Z: 5, 6");
		mlx_string_put(a, b, x + 348, y + 27, 0x00FFFFFF, "Slide");
		mlx_string_put(a, b, x + 320, y + 47, 0x00FFFFFF, "Arrow Keys");
		mlx_string_put(a, b, x + 547, y, 0x00FFFFFF, "Reset");
		mlx_string_put(a, b, x + 533, y + 20, 0x00FFFFFF, "Spacebar");
		mlx_string_put(a, b, x + 550, y + 55, 0x00FFFFFF, "Zoom");
		mlx_string_put(a, b, x + 490, y + 75, 0x00FFFFFF, "Z / X / Trackball");
	}
}
