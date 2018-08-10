/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 17:02:56 by mcarney           #+#    #+#             */
/*   Updated: 2018/07/24 17:03:02 by mcarney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "libft/libft.h"
# include "mlx.h"

typedef struct		s_px
{
	int				x;
	int				y;
	int				z;
	int				tmpx;
	int				tmpy;
}					t_px;

typedef struct		s_wf
{
	void			*mlx;
	void			*win;
	void			*img;
	t_px			**pxs;
	int				win_h;
	int				win_w;
	int				file_h;
	int				file_w;
	int				xdegrees;
	int				ydegrees;
	int				zdegrees;
	int				zoom;
	char			*addr;
	int				bpp;
	int				bytes;
	int				endian;
	int				yslide;
	int				xslide;
	unsigned int	color;
}					t_wf;

void				calibrate(t_wf *wf);
void				display(t_wf *wf);
void				defaults(t_wf *wf);
void				fill_array(char *filename, t_wf *wf, int y);
void				count_and_error_check(char *filename, t_wf *wf);
int					key_press_hook(int keycode, t_wf *wf);
int					deal_mouse(int button, int x, int y, t_wf *wf);
void				decorate_win(void *a, void *b, int x, int y);

#endif
