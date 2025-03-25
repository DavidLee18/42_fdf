/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 01:28:19 by jaehylee          #+#    #+#             */
/*   Updated: 2025/03/26 02:08:52 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

	if (mat->col != 3 || mat->ptr->len != 1)
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
