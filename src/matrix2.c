/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 01:28:19 by jaehylee          #+#    #+#             */
/*   Updated: 2025/03/31 19:21:07 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

int	dot_prod(t_vec row, t_matrix *mat, size_t col)
{
	int		res;
	size_t	k;

	res = 0;
	k = 0;
	while (k < mat->col)
	{
		res += row.ptr[k] * mat->ptr[k].ptr[col];
		k++;
	}
	return (res);
}

t_matrix	*rotate(t_list **dyn, double angx, double angy, t_matrix *mat)
{
	t_matrix	*vrot;
	t_matrix	*hrot;
	t_matrix	*res;

	if (mat->col != 3)
		return (NULL);
	vrot = get_vrot(dyn, angy);
	hrot = get_hrot(dyn, angx);
	if (vrot == NULL || hrot == NULL)
		return (NULL);
	res = matmul(dyn, vrot, mat);
	if (res == NULL)
		return (NULL);
	return (matmul(dyn, hrot, res));
}

t_matrix	*get_vrot(t_list **dyn, double angle)
{
	t_matrix	*rot;

	rot = _3d_point_col(dyn, SCALE * cos(angle), 0, SCALE * sin(angle));
	if (rot == NULL)
		return (NULL);
	if (_3d_point_col(dyn, 0, SCALE, 0) == NULL
		|| mat2vec(dyn, _3d_point_col(dyn, 0, SCALE, 0)) == NULL)
		return (NULL);
	add_col(dyn, *mat2vec(dyn, _3d_point_col(dyn, 0, SCALE, 0)), rot);
	if (_3d_point_col(dyn, SCALE * sin(angle), 0, SCALE * cos(angle))
		== NULL || mat2vec(dyn, _3d_point_col(dyn, -SCALE * sin(angle), 0,
				SCALE * cos(angle))) == NULL)
		return (NULL);
	add_col(dyn, *mat2vec(dyn, _3d_point_col(dyn, -SCALE * sin(angle), 0,
				SCALE * cos(angle))), rot);
	return (rot);
}

t_matrix	*get_hrot(t_list **dyn, double angle)
{
	t_matrix	*rot;

	rot = _3d_point_col(dyn, SCALE, 0, 0);
	if (rot == NULL)
		return (NULL);
	if (_3d_point_col(dyn, 0, SCALE * cos(angle), -SCALE * sin(angle))
		== NULL || mat2vec(dyn, _3d_point_col(dyn, 0, SCALE * cos(angle),
				-SCALE * sin(angle))) == NULL)
		return (NULL);
	add_col(dyn, *mat2vec(dyn, _3d_point_col(dyn, 0, SCALE * cos(angle),
				-SCALE * sin(angle))), rot);
	if (_3d_point_col(dyn, 0, SCALE * sin(angle), SCALE * cos(angle))
		== NULL || mat2vec(dyn, _3d_point_col(dyn, 0, SCALE * sin(angle),
				SCALE * cos(angle))) == NULL)
		return (NULL);
	add_col(dyn, *mat2vec(dyn, _3d_point_col(dyn, 0, SCALE * sin(angle),
				SCALE * cos(angle))), rot);
	return (rot);
}

t_matrix	*ortho_proj(t_list **dyn, t_matrix *mat)
{
	t_matrix	*proj;

	proj = _3d_point_col(dyn, 1, 0, 0);
	if (proj == NULL)
		return (NULL);
	if (_3d_point_col(dyn, 0, 1, 0) == NULL
		|| mat2vec(dyn, _3d_point_col(dyn, 0, 1, 0)) == NULL)
		return (NULL);
	add_col(dyn, *mat2vec(dyn, _3d_point_col(dyn, 0, 1, 0)), proj);
	if (_3d_point_col(dyn, 0, 0, 0) == NULL
		|| mat2vec(dyn, _3d_point_col(dyn, 0, 0, 0)) == NULL)
		return (NULL);
	add_col(dyn, *mat2vec(dyn, _3d_point_col(dyn, 0, 0, 0)), proj);
	return (matmul(dyn, proj, mat));
}
