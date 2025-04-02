/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 22:26:28 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/03 01:54:00 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_list	*dyn;
	t_fdf	*fdf;

	if (argc != 2)
		return (ft_fprintf(STDERR_FILENO, "usage: %s *.fdf\n", argv[0]), 0);
	dyn = NULL;
	fdf = parse_fdf(&dyn, argv[1]);
	if (fdf == NULL || fdf->dim == NULL)
		return (ft_fprintf(STDERR_FILENO, "failed to parse %s\n", argv[1]),
			gc_free_all(dyn), 0);
	fdf->dim->y = fdf->points->ptr->len / fdf->dim->x;
	fdf->points = rotate2(&dyn, -M_PI_4, rotate(&dyn, M_PI * 5 / 16,
				M_PI * 13 / 16, fdf->points));
	fdf->points = ortho_proj(&dyn, fdf->points);
	if (fdf->points == NULL)
		return (ft_fprintf(STDERR_FILENO, "failed to rotate\n"), cleanup(fdf),
			0);
	if (!draw_fdf(fdf))
		return (cleanup(fdf), 0);
	mlx_key_hook(fdf->win, on_key, fdf);
	mlx_hook(fdf->win, 0x21, 0, cleanup, fdf);
	mlx_loop(fdf->mlx);
	return (0);
}

int	on_key(int keycode, t_fdf *f)
{
	if (keycode == ESC)
		return (cleanup(f));
	return (0);
}

int	cleanup(t_fdf *f)
{
	mlx_destroy_image(f->mlx, f->img->img);
	mlx_destroy_window(f->mlx, f->win);
	mlx_destroy_display(f->mlx);
	free(f->mlx);
	gc_free_all(*f->dyn);
	exit(0);
	return (0);
}
