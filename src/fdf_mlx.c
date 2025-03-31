/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 21:36:28 by jaehylee          #+#    #+#             */
/*   Updated: 2025/03/31 19:17:36 by jaehylee         ###   ########.fr       */
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
	if (fd < 0)
		return (NULL);
	f->points = atoi_split(dyn, fd);
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
	t_point2	p;
	t_point2	prev;

	i = 0;
	p = (t_point2){0, 0};
	prev = (t_point2){0, 0};
	while (i < f->points->ptr->len)
	{
		p.x = clamp(f->points->ptr->ptr[i] + 300, 0, WIN_WIDTH);
		p.y = clamp(f->points->ptr[1].ptr[i], 0, WIN_HEIGHT);
		put_pixel(f->img, p.x, p.y, 0xFF0000);
		if (i > 0)
			draw_line(f->img, prev, p);
		prev = p;
		i++;
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img->img, 0, 0);
	return (1);
}

void	draw_line(t_img *img, t_point2 p1, t_point2 p2)
{
	t_point2	d;
	t_point2	p;

	d = (t_point2){p2.x - p1.x, p2.y - p1.y};
	p = p1;
	while (p.x != p2.x || p.y != p2.y)
	{
		put_pixel(img, p.x, p.y, 0xFF0000);
		p.x += ((d.x > 0) * 2 - 1) * (d.x != 0);
		p.y += ((d.y > 0) * 2 - 1) * (d.y != 0);
	}
}
