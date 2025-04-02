/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mlx3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:20:00 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/02 07:49:30 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_max_dy(t_matrix *mat)
{
	int		dy;
	int		prev;
	size_t	i;

	dy = 0;
	i = 0;
	prev = 0;
	if (mat->col == 0)
		return (0);
	while (i < mat->ptr->len)
	{
		if (mat->ptr[1].ptr[i] < 0)
			dy = -mat->ptr[1].ptr[i];
		else if (mat->ptr[1].ptr[i] > PIC_HEIGHT)
			dy = PIC_HEIGHT - mat->ptr[1].ptr[i];
		if (abs(prev) > abs(dy))
			dy = prev;
		prev = dy;
		i++;
	}
	return (dy);
}

void	draw_lines(t_fdf *f)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < (size_t)f->dim->y)
	{
		j = 0;
		while (j < (size_t)f->dim->x)
		{
			if (j + 1 != (size_t)f->dim->x)
				draw_line(f->img, coord(f->points, i, j, f->dim),
					coord(f->points, i, j + 1, f->dim));
			if (i + 1 != (size_t)f->dim->y)
				draw_line(f->img, coord(f->points, i, j, f->dim),
					coord(f->points, i + 1, j, f->dim));
			j++;
		}
		i++;
	}
}

t_point2	coord(t_matrix *points, int row, int col, t_point2 *dim)
{
	return ((t_point2){points->ptr->ptr[(int)row
			* dim->x + col], points->ptr[1].ptr[(int)row
			* dim->x + col]});
}
