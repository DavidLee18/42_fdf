/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mlx3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:20:00 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/02 21:23:58 by jaehylee         ###   ########.fr       */
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
		draw_line(f->img, coord(f->points, i),
			coord(f->points, i + 1));
		i++;
	}
}

t_point2	coord(t_matrix *points, int raw)
{
	return ((t_point2){points->ptr->ptr[raw], points->ptr[1].ptr[raw]});
}
