/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 22:26:28 by jaehylee          #+#    #+#             */
/*   Updated: 2025/03/31 04:39:04 by jaehylee         ###   ########.fr       */
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
	if (fdf == NULL)
		return (ft_fprintf(STDERR_FILENO, "failed to parse %s\n", argv[1]),
			gc_free_all(dyn), 0);
	fdf->points = rotate(&dyn, atan(sin(M_PI_4)), M_PI_4, fdf->points);
	if (fdf->points == NULL)
		return (ft_fprintf(STDERR_FILENO, "failed to rotate\n"), cleanup(fdf),
			free(fdf->mlx), gc_free_all(dyn), 0);
	fdf->points = ortho_proj(&dyn, fdf->points);
	if (fdf->points == NULL)
		return (ft_fprintf(STDERR_FILENO, "failed to project\n"), cleanup(fdf),
			free(fdf->mlx), gc_free_all(dyn), 0);
	draw_fdf(fdf);
	mlx_key_hook(fdf->win, on_key, fdf);
	mlx_hook(fdf->win, 0x21, 0, cleanup, fdf);
	mlx_loop(fdf->mlx);
	return (free(fdf->mlx), gc_free_all(dyn), 0);
}

int	on_key(int keycode, t_fdf *f)
{
	ft_fprintf(STDOUT_FILENO, "key: %#X\n", keycode);
	(void)f->mlx;
	return (0);
}

int	cleanup(t_fdf *f)
{
	mlx_destroy_image(f->mlx, f->img->img);
	mlx_destroy_window(f->mlx, f->win);
	mlx_destroy_display(f->mlx);
	return (0);
}
