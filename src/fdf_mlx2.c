/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mlx2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:06:10 by jaehylee          #+#    #+#             */
/*   Updated: 2025/03/31 21:47:18 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

size_t	get_max_width(t_matrix *mat)
{
	size_t	w;
	size_t	i;
	int		prev;

	w = 0;
	i = 0;
	prev = mat->ptr->ptr[0];
	if (mat->col == 0)
		return (0);
	while (i < mat->ptr->len)
	{
		if (w < (size_t)abs(mat->ptr->ptr[i] - prev))
			w = (size_t)abs(mat->ptr->ptr[i] - prev);
		i++;
	}
	return (w);
}

size_t	get_max_height(t_matrix *mat)
{
	size_t	h;
	size_t	i;
	int		prev;

	h = 0;
	i = 0;
	prev = mat->ptr->ptr[0];
	if (mat->col == 0)
		return (0);
	while (i < mat->ptr->len)
	{
		if (h < (size_t)abs(mat->ptr[1].ptr[i] - prev))
			h = (size_t)abs(mat->ptr[1].ptr[i] - prev);
		i++;
	}
	return (h);
}

void	fit_scale(t_fdf *f)
{
	size_t	x_scale;
	size_t	y_scale;
	size_t	factor;
	size_t	i;

	x_scale = (size_t)ceil((double)get_max_width(f->points)
			/ (double)WIN_WIDTH);
	y_scale = (size_t)ceil((double)get_max_height(f->points)
			/ (double)WIN_HEIGHT);
	factor = usize_max(x_scale, y_scale);
	i = 0;
	while (i < f->points->ptr->len)
	{
		f->points->ptr->ptr[i] = (size_t)round((double)f->points->ptr->ptr[i]
				/ (double)factor);
		f->points->ptr[1].ptr[i] = (size_t)round((double)f->points->ptr[1]
				.ptr[i] / (double)factor);
		i++;
	}
}
