/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mlx3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:20:00 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/01 09:48:23 by jaehylee         ###   ########.fr       */
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
		else if (mat->ptr[1].ptr[i] > WIN_HEIGHT)
			dy = WIN_HEIGHT - mat->ptr[1].ptr[i];
		if (abs(prev) > abs(dy))
			dy = prev;
		prev = dy;
		i++;
	}
	return (dy);
}
