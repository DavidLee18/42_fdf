/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 21:36:28 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/02 02:14:54 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_fdf	*parse_fdf(t_list **dyn, char *path)
{
	t_fdf	*f;
	int		fd;

	f = (t_fdf *)gc_calloc(dyn, 1, sizeof(t_fdf));
	if (f == NULL)
		return (NULL);
	fd = open(path, O_RDONLY);
	f->dim = (t_point2 *)gc_calloc(dyn, 1, sizeof(t_point2));
	if (fd < 0 || f->dim == NULL)
		return (NULL);
	f->points = atoi_split(dyn, fd, f->dim);
	if (f->points == NULL)
		return (NULL);
	f->mlx = mlx_init();
	if (f->mlx == NULL)
		return (NULL);
	f->win = mlx_new_window(f->mlx, WIN_WIDTH, WIN_HEIGHT, path);
	if (f->win == NULL)
		return (free(f->mlx), NULL);
	if (!init_img(dyn, f->mlx, &f->img))
		return (mlx_destroy_window(f->mlx, f->win), free(f->mlx), NULL);
	f->dyn = dyn;
	return (f);
}

_Bool	init_img(t_list **dyn, void *mlx, t_img **img)
{
	*img = (t_img *)gc_calloc(dyn, 1, sizeof(t_img));
	if (*img == NULL)
		return (0);
	(*img)->img = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	if ((*img)->img == NULL)
		return (0);
	(*img)->addr = mlx_get_data_addr((*img)->img, &(*img)->bits_per_pixel,
			&(*img)->line_len, &(*img)->endian);
	if ((*img)->addr == NULL)
		return (mlx_destroy_image(mlx, (*img)->img), 0);
	return (1);
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	*((unsigned int *)(img->addr
				+ (y * img->line_len + x * (img->bits_per_pixel / 8)))) = color;
}

_Bool	draw_fdf(t_fdf *f)
{
	size_t		i;

	i = 0;
	fit_scale(f);
	fit_pos(f);
	while (i < f->points->ptr->len)
	{
		put_pixel(f->img, f->points->ptr->ptr[i],
			f->points->ptr[1].ptr[i], 0xFF0000);
		i++;
	}
	draw_lines(f);
	mlx_put_image_to_window(f->mlx, f->win, f->img->img, 0, 0);
	return (1);
}

void	draw_line(t_img *img, t_point2 p1, t_point2 p2)
{
	double	m;
	int		x;
	int		y;

	if (p1.x == p2.x)
	{
		y = p1.y;
		while (y != p2.y)
		{
			put_pixel(img, p1.x, y, 0xFF0000);
			y += (y < p2.y) * 2 - 1;
		}
		return ;
	}
	m = (double)(p2.y - p1.y) / (double)(p2.x - p1.x);
	x = p1.x;
	y = p1.y;
	while (x != p2.x || y != p2.y)
	{
		put_pixel(img, x, y, 0xFF0000);
		x += (p2.x > x) * 2 - 1;
		y = (int)((double)p1.y + m * (double)(x - p1.x));
	}
}
