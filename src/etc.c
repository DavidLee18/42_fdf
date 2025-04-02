/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 21:56:03 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/02 21:46:24 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_matrix	*atoi_split(t_list **dyn, int fd, t_point2 *dim)
{
	char		*str;
	t_matrix	*row;
	char		**tmp;
	t_matrix	*mat;
	size_t		i;

	str = gc_getline(dyn, fd);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (str != NULL && str[0] != '\0')
	{
		tmp = gc_split(dyn, str, ' ');
		if (tmp == NULL)
			return (NULL);
		row = atoi_push(dyn, tmp, i++, dim);
		if (i == 1)
			mat = row;
		else if (row != NULL)
			mat = append(dyn, mat, row);
		if (mat == NULL || row == NULL)
			return (dim = NULL, NULL);
		str = gc_getline(dyn, fd);
	}
	return (transpose(dyn, mat));
}

t_matrix	*atoi_push(t_list **dyn, char **nums, size_t row, t_point2 *dim)
{
	t_vec		*v;
	size_t		i;
	int			*j;
	t_matrix	*res;

	res = (t_matrix *)gc_calloc(dyn, 1, sizeof(t_matrix));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (nums[i])
	{
		j = atoi_(dyn, nums[i]);
		if (j == NULL)
			return (NULL);
		v = mat2vec(dyn, _3d_point_col(dyn, (int)row, (int)i++, *j));
		if (v == NULL || !add_row(dyn, *v, res))
			return (NULL);
	}
	dim->x = i;
	return (res);
}

int	*atoi_(t_list **dyn, const char *str)
{
	int		*res;
	long	temp;
	size_t	i;
	int		sign;

	res = (int *)gc_calloc(dyn, 1, sizeof(int));
	if (res == NULL)
		return (NULL);
	temp = 0;
	if (str[0] != '-' && str[0] != '+' && (str[0] < '0' || str[0] > '9'))
		return (NULL);
	sign = (str[0] != '-') * 2 - 1;
	i = (str[0] == '-' || str[0] == '+');
	while (i < ft_strlen(str))
	{
		if (str[i] < '0' || str[i] > '9')
			return (NULL);
		temp = 10 * temp + sign * (str[i] - '0');
		i++;
	}
	if (temp < INT_MIN_ || temp > INT_MAX_ || (ft_strlen(str) == 1 && sign
			&& !temp && ft_strncmp(str, "0", 1)))
		return (NULL);
	*res = (int)temp;
	return (res);
}

int	clamp(int val, int min, int max)
{
	if (val < min)
		return (min);
	if (val > max)
		return (max);
	return (val);
}
