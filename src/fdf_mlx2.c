/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mlx2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:06:10 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/02 14:36:31 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

size_t	get_max_width(t_matrix *mat)
{
	int		wmax;
	int		wmin;
	size_t	i;

	wmax = 0;
	wmin = 0;
	i = 0;
	if (mat->col == 0)
		return (0);
	while (i < mat->ptr->len)
	{
		if (wmax < mat->ptr->ptr[i])
			wmax = mat->ptr->ptr[i];
		if (wmin > mat->ptr->ptr[i])
			wmin = mat->ptr->ptr[i];
		i++;
	}
	return (wmax - wmin);
}

size_t	get_max_height(t_matrix *mat)
{
	int		hmax;
	int		hmin;
	size_t	i;

	hmax = 0;
	hmin = 0;
	i = 0;
	if (mat->col == 0)
		return (0);
	while (i < mat->ptr[1].len)
	{
		if (hmax < mat->ptr[1].ptr[i])
			hmax = mat->ptr[1].ptr[i];
		if (hmin > mat->ptr[1].ptr[i])
			hmin = mat->ptr[1].ptr[i];
		i++;
	}
	return (hmax - hmin);
}

void	fit_scale(t_fdf *f)
{
	size_t	x_scale;
	size_t	y_scale;
	size_t	factor;
	size_t	i;

	x_scale = (size_t)ceil((double)get_max_width(f->points)
			/ (double)PIC_WIDTH);
	y_scale = (size_t)ceil((double)get_max_height(f->points)
			/ (double)PIC_HEIGHT);
	factor = usize_max(x_scale, y_scale);
	i = 0;
	while (i < f->points->ptr->len)
	{
		f->points->ptr->ptr[i] = (int)round((double)f->points->ptr->ptr[i]
				/ (double)factor);
		f->points->ptr[1].ptr[i] = (int)round((double)f->points->ptr[1]
				.ptr[i] / (double)factor);
		i++;
	}
}

void	fit_pos(t_fdf *f)
{
	const int	dx = get_max_dx(f->points);
	const int	dy = get_max_dy(f->points);
	size_t		i;

	i = 0;
	while (i < f->points->ptr->len)
	{
		f->points->ptr->ptr[i] += dx;
		f->points->ptr[1].ptr[i] += dy;
		i++;
	}
}

int	get_max_dx(t_matrix *mat)
{
	int		dx;
	int		prev;
	size_t	i;

	dx = 0;
	i = 0;
	prev = 0;
	if (mat->col == 0)
		return (0);
	while (i < mat->ptr->len)
	{
		if (mat->ptr->ptr[i] < 0)
			dx = -mat->ptr->ptr[i];
		else if (mat->ptr->ptr[i] > PIC_WIDTH)
			dx = PIC_WIDTH - mat->ptr->ptr[i];
		else
			dx = 0;
		if (abs(prev) > abs(dx))
			dx = prev;
		prev = dx;
		i++;
	}
	return (dx);
}
