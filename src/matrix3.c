/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:38:56 by jaehylee          #+#    #+#             */
/*   Updated: 2025/03/27 12:56:32 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_matrix	*_3d_point_col(t_list **dyn, int x, int y, int z)
{
	t_matrix	*p;
	t_vec		v;

	p = (t_matrix *)gc_calloc(dyn, 1, sizeof(t_matrix));
	if (p == NULL)
		return (NULL);
	p->col = 0;
	p->cap = 0;
	v = (t_vec){.ptr = NULL, .len = 0, .cap = 0};
	push_back(dyn, &v, x);
	add_row(dyn, v, p);
	v.ptr[0] = y;
	add_row(dyn, v, p);
	v.ptr[0] = z;
	add_row(dyn, v, p);
	return (p);
}

t_vec	*mat2vec(t_list **dyn, t_matrix *mat)
{
	t_vec	v;
	size_t	i;

	if (mat->col != 1 && mat->col > 0 && mat->ptr[0].len != 1)
		return (NULL);
	if (mat->col == 1)
		return (veccpy(dyn, mat->ptr[0]));
	v = (t_vec){.ptr = NULL, .len = 0, .cap = 0};
	i = 0;
	while (i < mat->col)
	{
		push_back(dyn, &v, mat->ptr[i].ptr[0]);
		i++;
	}
	return (veccpy(dyn, v));
}
