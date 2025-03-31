/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 21:36:28 by jaehylee          #+#    #+#             */
/*   Updated: 2025/03/31 12:18:31 by jaehylee         ###   ########.fr       */
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
	f->win = mlx_new_window(f->mlx, 1920, 1080, path);
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
	(*img)->img = mlx_new_image(mlx, 1080, 1080);
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

void	draw_fdf(t_fdf *f)
{
	size_t	i;
	int		x;
	int		y;

	i = 0;
	x = 0;
	y = 0;
	while (i < f->points->ptr->len)
	{
		ft_fprintf(STDOUT_FILENO, "(%4d, %4d) ", f->points->ptr->ptr[i],
			f->points->ptr[1].ptr[i]);
		x = clamp(f->points->ptr->ptr[i] + 300, 0, 1920);
		y = clamp(f->points->ptr[1].ptr[i], 0, 1080);
		put_pixel(f->img, x, y, 0xFF0000);
		i++;
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img->img, 0, 0);
}
