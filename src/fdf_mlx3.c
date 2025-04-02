/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mlx3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:20:00 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/03 02:15:38 by jaehylee         ###   ########.fr       */
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
		else
			dy = 0;
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

	i = 0;
	while (i < f->points->ptr->len)
	{
		if (i + f->dim->x >= f->points->ptr->len
			|| i + f->dim->x >= f->points->ptr[1].len)
		{
			i++;
			continue ;
		}
		draw_line(f->img, coord(f->points, i),
			coord(f->points, i + f->dim->x));
		if ((int)(i + 1) % f->dim->x != 0)
			draw_line(f->img, coord(f->points, i),
				coord(f->points, i + 1));
		i++;
	}
}

t_point2	coord(t_matrix *points, int raw)
{
	return ((t_point2){points->ptr->ptr[raw], points->ptr[1].ptr[raw]});
}

t_matrix	*get_zrot(t_list **dyn, double angle)
{
	t_matrix	*rot;

	rot = _3d_point_col(dyn, SCALE * cos(angle), SCALE * sin(angle), 0);
	if (rot == NULL)
		return (NULL);
	if (_3d_point_col(dyn, -SCALE * sin(angle), SCALE * cos(angle), 0) == NULL
		|| mat2vec(dyn, _3d_point_col(dyn, -SCALE * sin(angle),
				SCALE * cos(angle), 0)) == NULL)
		return (NULL);
	add_col(dyn, *mat2vec(dyn, _3d_point_col(dyn, -SCALE * sin(angle),
				SCALE * cos(angle), 0)), rot);
	if (_3d_point_col(dyn, 0, 0, SCALE)
		== NULL || mat2vec(dyn, _3d_point_col(dyn, 0, 0, SCALE)) == NULL)
		return (NULL);
	add_col(dyn, *mat2vec(dyn, _3d_point_col(dyn, 0, 0, SCALE)), rot);
	return (rot);
}

t_matrix	*rotate2(t_list **dyn, double angz, t_matrix *mat)
{
	t_matrix	*zrot;

	zrot = get_zrot(dyn, angz);
	if (zrot == NULL)
		return (NULL);
	return (matmul(dyn, zrot, mat));
}
